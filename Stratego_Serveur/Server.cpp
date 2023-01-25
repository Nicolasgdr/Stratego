#include "Server.h"
#include "../Stratego_libs/Model/action_send.h"
#include "../Stratego_libs/Stratego-encap/json_interpreter.h"
#include "../Stratego_libs/Stratego-encap/json_generator.h"
#include "dto/userDto.h"
#include "dto/statDto.h"
#include "dto/pauseDto.h"
#include "dao/pauseDao.h"
#include "repository/userrepository.h"
#include "repository/statrepository.h"
#include "repository/historyrepository.h"
#include "repository/pauseRepository.h"
#include "QSqlQuery"
#include "QSqlError"
#include <cstdlib>
#include <ctime>

Server::Server(QObject*parent): QTcpServer(parent),clientId(0),gameId(0){
	const QString DRIVER("QSQLITE");
        if(QSqlDatabase::isDriverAvailable(DRIVER))
        {
            db = QSqlDatabase::addDatabase(DRIVER);
            db.setDatabaseName("stratego.db");
        }
        if(db.open()){
            QSqlQuery query;
            query.exec("SELECT count(*) as nb FROM sqlite_master WHERE type = 'table'");
            query.exec("SELECT count(*) as nb FROM sqlite_master WHERE type = 'table' AND tbl_name = 'HISTORY'");
            query.first();
            if(query.value(0) == 0){
                query.clear();
                query.exec("CREATE TABLE HISTORY(id    INTEGER NOT NULL,user1 INTEGER NOT NULL,user2 INTEGER NOT NULL,"
                                           "winner varchar(255) NOT NULL ,PRIMARY KEY(id AUTOINCREMENT),"
                                           "FOREIGN KEY(user1) REFERENCES USER(id)"
                                           "FOREIGN KEY(user2) REFERENCES USER(id)"
                                           "FOREIGN KEY(winner) REFERENCES USER(name))");
                query.exec("CREATE TABLE STAT(id INTEGER NOT NULL,name varchar(255) NOT NULL UNIQUE, nbVictory INTEGER,PRIMARY KEY(id AUTOINCREMENT)"
                           "FOREIGN KEY(name) REFERENCES USER(name))");
                query.exec("CREATE TABLE USER(id INTEGER NOT NULL,name varchar(255) NOT NULL UNIQUE,PRIMARY KEY(id AUTOINCREMENT))");
                query.exec("CREATE TABLE PAUSE(id INTEGER NOT NULL,name varchar(255) NOT NULL, gameId INTEGER UNIQUE,PRIMARY KEY(id AUTOINCREMENT)"
                           "FOREIGN KEY(name) REFERENCES USER(name))");

            }
            query.clear();
        }
}

int Server::genRandomInt(){
    std::srand(std::time(nullptr));
    int random_number = std::rand() % 3;
    return random_number;
}

void Server::refreshLobbies() const{
    for(auto connection : connections){
        if(!connection->isInGame())
            emit connection->send_data(json_generator::refresh_lobby(lobbiesInfo,connections.size(),connection->getStat()));
    }
}

bool Server::removeLobby(int id){
    auto begin = lobbiesInfo.begin();
    bool removed = false;
    while(!removed && begin != lobbiesInfo.end()){
        if(get<0>(*begin) == id){
            lobbiesInfo.erase(begin);
            removed = true;
        }
        begin++;
    }
    return removed;
}

void Server::sendData(const std::tuple<std::unique_ptr<Game>, ConnectionToClient *, ConnectionToClient *>& tuple)const{
    emit get<1>(tuple)->send_data(json_generator::send_data(
                                     get<0>(tuple).get(),
                                     get<1>(tuple)->getColor(),
                                     get<1>(tuple)->getPlayerPseudo()));
    if(!get<0>(tuple)->is_against_bot()){
        emit get<2>(tuple)->send_data(json_generator::send_data(
                                         get<0>(tuple).get(),
                                         get<2>(tuple)->getColor(),
                                         get<2>(tuple)->getPlayerPseudo()));
    }
}

int Server::getIndexTuple(ConnectionToClient* cli) const{
    auto begin = gameHandler.begin();
    int index = 0;
    while(begin != gameHandler.end()){
        if(get<1>(*begin) == cli || get<2>(*begin) == cli){
            return index;
        }
        begin++;
        index++;
    }
    return -1;
}

void Server::removeTuple(int index){
    qDebug()<<"remove tuple"<< index;
    if(index < (int) gameHandler.size() && index >= 0){
        get<0>(gameHandler.at(index)).release();
        gameHandler.erase(gameHandler.begin() + index);
        qDebug()<<"game removed";
    }
}

void Server::start_server(){
    if(this->listen(QHostAddress("localhost"),nbPort))
    {
        qDebug()<< "-----------------------------------\n" <<"Server online, listening for incoming connections "
                << "on port " << nbPort <<"\n-----------------------------------\n";

    }else
    {
        qDebug()<<"Server not connectect error...\n";
    }
}

const std::vector<ConnectionToClient*> Server::getConnectedClients() const{
    return connections;
}

unsigned Server::getNbConnections() const{
    return connections.size();
}

bool Server::gameReloader(ConnectionToClient* cli, QByteArray data){
    int gId = json_interpreter::unpacked_reload_game(data);
    QString name = cli->getPlayerPseudo();
    if(checkPauseDb(gId,name)){
        auto begin = gameHandler.begin();
        while(begin != gameHandler.end()){
            if(get<0>(*begin)->get_game_id() == gId){
                qDebug()<<"gId found";
                get<1>(*begin) = cli;
                cli->setGameId(gId);
                cli->setInGame(true);
                cli->setPlayerColor(RED);
                sendData(*begin);
                removePauseFromDb(name,gId);
                qDebug()<<"after remove pause from db";
                return true;
            }
            begin++;
        }
    }else emit cli->send_data(json_generator::error("Wrong game id"));
    return false;
}

bool Server::checkLobby(int idx){
    bool isPublic = false;
    if(idx != -1){
        if(!get<0>(gameHandler.at(idx))->is_private()){
            isPublic = true;
            removeLobby(get<0>(gameHandler.at(idx))->get_game_id());
        }
        removeTuple(idx);
    }
    return isPublic;
}

void Server::handleMessageFromClient(QByteArray data, ConnectionToClient* cli){
    Action_send msg = json_interpreter::get_type(data);
    switch (msg) {
        case CONNECTION_TO_SERVER:{
            statRepository sRep;
            QString playerId = json_interpreter::unpacked_connection_to_server(data);
            checkDbUser(playerId);
            int vict = sRep.getNbVictory(playerId.toStdString());
            cli->setPlayerPseudo(playerId);
            cli->setStat(vict);
            refreshLobbies();
            break;
        }
        case CREATE_GAME:{
            game_begin beginInfo = json_interpreter::unpacked_create_game(data);
            cli->setGameId(gameId);
            qDebug()<<"CG "<<cli->getPlayerPseudo() <<cli->getGameId();
            cli->setPlayerColor(beginInfo.creator.getColor());
            gameHandler.push_back(std::make_tuple(std::make_unique<Game>(Game(gameId, beginInfo.isPrivate, beginInfo.soloGame)),cli,nullptr));
            get<0>(gameHandler.back())->addPlayer(beginInfo.creator);
            Color color = (beginInfo.creator.getColor() == Color::RED) ? Color::BLUE : Color::RED;
            if(!beginInfo.isPrivate && !beginInfo.soloGame){
                lobbiesInfo.push_back(std::make_tuple(gameId,beginInfo.creator.get_pseudo(),color));
                refreshLobbies();
            }
            if(beginInfo.isPrivate){
                emit cli->send_data(json_generator::private_game(gameId));
            }
            if(beginInfo.soloGame){
                get<1>(gameHandler.back())->setInGame(true);
                get<0>(gameHandler.back())->addPlayer(Player("bot",color));
                get<0>(gameHandler.back())->start();
                QString path = "./placement/file_placement" + QString::number(genRandomInt())+".txt";
                get<0>(gameHandler.back())->file_placement(path.toStdString(),color);
                get<0>(gameHandler.back())->setBotBoard();
                emit get<1>(gameHandler.back())->send_data(json_generator::send_data(get<0>(gameHandler.back()).get(),
                                                                                get<1>(gameHandler.back())->getColor(),
                                                                                get<1>(gameHandler.back())->getPlayerPseudo()));
            }
            gameId++;
            break;
        }
        case LAUNCH_GAME:{
            secondPlayerInfo playerInfo = json_interpreter::unpacked_launch_game(data);
            bool found = false;
            auto begin = gameHandler.begin();
            int tupleToRemove = -1;
            int lobbyToRemove = -1;
            while(!found && begin != gameHandler.end()){
                if(!get<0>(*begin)->is_against_bot() && get<0>(*begin)->get_state() == NOT_STARTED
                        && get<0>(*begin)->get_game_id() == playerInfo.gameId){
                    //the client has a lobby (private or public) but joining another one
                    if(cli->getGameId() >= 0){
                        if(cli->getGameId() == playerInfo.gameId){
                            emit cli->send_data(json_generator::error("You cannot not join your own game."));
                            return;
                        }else{
                            tupleToRemove = getIndexTuple(cli);
                            lobbyToRemove = cli->getGameId();
                        }
                    }
                    cli->setGameId(get<0>(*begin)->get_game_id());
                    if(playerInfo.player.getColor() != NONE){
                        cli->setPlayerColor(playerInfo.player.getColor());
                        get<0>(*begin)->addPlayer(playerInfo.player);
                    }else{
                        (get<0>(*begin)->get_players()[0].getColor() == RED) ?
                                    cli->setPlayerColor(BLUE) : cli->setPlayerColor(RED);
                        get<0>(*begin)->addPlayer(Player(cli->getPlayerPseudo(),cli->getColor()));
                    }
                    get<2>(*begin) = cli;
                    get<2>(*begin)->setInGame(true);
                    get<1>(*begin)->setInGame(true);
                    //NOT_STARTED -> PLACEMENT
                    get<0>(*begin)->start();
                    sendData(*begin);
                    if(!get<0>(*begin)->is_private())
                        removeLobby(playerInfo.gameId);
                    found = true;
                }
                begin++;
            }
            if(!found) emit cli->send_data(json_generator::error("The given game does not exist"));
            else{
                removeTuple(tupleToRemove);
                removeLobby(lobbyToRemove);
                refreshLobbies();
            }
            break;
        }
        case PLACE_PAWN:{
            int index = getIndexTuple(cli);
            Game* g = get<0>(gameHandler.at(index)).get();
            if(g->get_state() == GameState::PLACEMENT){
                placement place = json_interpreter::unpacked_place_pawn(data);
                int row = place.position.getRow();
                int column = place.position.getColumn();
                try{
                    g->manual_placement(row,column,place.rank,place.player_color);
                    //in case if the bot is the first player to move a pawn
                    if(g->get_state() == PLAYER_TURN && g->is_against_bot() &&
                            g->get_current_player() == g->get_players().at(1).getColor()){
                        Color c = g->get_players()[1].getColor();
                        std::array<std::array<int,2>,2> m = g->genMove();
                        g->move_piece(m.at(0)[0],m.at(0)[1],m.at(1)[0],m.at(1)[1],c);
                        g->next_player();
                    }
                    sendData(gameHandler.at(index));
                }
                catch(const std::invalid_argument& e){emit cli->send_data(json_generator::error(e.what()));}
                catch(const std::out_of_range& e){emit cli->send_data(json_generator::error(e.what()));}
            }
            break;
        }
        case MOVE_PAWN:{
            int index = getIndexTuple(cli);
            Game* g = get<0>(gameHandler.at(index)).get();
            if(g->get_state() == GameState::PLAYER_TURN){
                moveInfo move = json_interpreter::unpacked_move_pawn(data);
                try{
                    int startRow = move.begin.getRow();
                    int startCol = move.begin.getColumn();
                    int endRow = move.end.getRow();
                    int endCol = move.end.getColumn();
                    g->move_piece(startRow,startCol,endRow,endCol,move.currentPlayerCol);
                    sendData(gameHandler.at(index));
                }
                catch(const state_error& e){emit cli->send_data(json_generator::error("Wait until all pawns are placed"));}
                catch(const std::invalid_argument& e){emit cli->send_data(json_generator::error(e.what()));}
            }
            break;
        }
        case TO_NEXT_PLAYER:{
            int index = getIndexTuple(cli);
            Game* g = get<0>(gameHandler.at(index)).get();
            if(g){
                try{
                    if(g->get_state() == GameState::NEXT_PLAYER)
                        g->next_player();
                    if(g->is_against_bot() && (g->get_state() == PLAYER_TURN)){
                        Color c = g->get_players()[1].getColor();
                        std::array<std::array<int,2>,2> m = g->genMove();
                        g->move_piece(m.at(0)[0],m.at(0)[1],m.at(1)[0],m.at(1)[1],c);
                        g->next_player();
                    }
                    if(g->get_state() == GameState::END_GAME){
                        emit get<1>(gameHandler.at(index))->send_data(json_generator::game_is_over(g->get_winner()));
                        if(!g->is_against_bot())
                            emit get<2>(gameHandler.at(index))->send_data(json_generator::game_is_over(g->get_winner()));
                        if(!get<0>(gameHandler.at(index))->is_private() && !get<0>(gameHandler.at(index))->is_against_bot())
                            removeLobby(get<0>(gameHandler.at(index))->get_game_id());
                        get<1>(gameHandler.at(index))->setInGame(false);
                        get<1>(gameHandler.at(index))->setGameId(-1);
                        if(!g->is_against_bot()){
                            get<2>(gameHandler.at(index))->setGameId(-1);
                            get<2>(gameHandler.at(index))->setInGame(false);
                        }
                        if(get<2>(gameHandler.at(index)) != nullptr){
                            addGameToHistoryDb(gameHandler.at(index));
                            refreshStat(gameHandler.at(index));
                        }
                        removeTuple(index);
                    }else{
                        sendData(gameHandler.at(index));
                    }
                }catch(state_error e){emit cli->send_data(json_generator::error(e.what()));}
            }
            break;
        }
        case DELETE_GAME:{
            removeTuple(getIndexTuple(cli));
            //refreshLobbies();
            break;
        }
        case RETURNING_TO_LOBBY:{
            emit cli->send_data(json_generator::refresh_lobby(lobbiesInfo,connections.size(),cli->getStat()));
            break;
        }
        case PAUSE:{
            addPauseToDb(cli->getPlayerPseudo(),cli->getGameId());
            emit cli->send_data(json_generator::game_pause(cli->getGameId()));
            int idx = getIndexTuple(cli);
            if(idx != -1)
                get<1>(gameHandler.at(idx)) = nullptr;
            cli->setInGame(false);
            cli->setGameId(-1);
            break;
        }
        case RELOAD_GAME:{
            qDebug()<<"reloading";
            int idx = getIndexTuple(cli);
            bool correct = gameReloader(cli,data);
            if(correct){
                bool wasPublic = checkLobby(idx);
                if(wasPublic)
                    refreshLobbies();
            }
            break;
        }
        default:{
            qDebug()<<"default";
            break;
        }
    }
}

bool Server::wasInGame(int idx, ConnectionToClient * ctc){
    if(idx != -1){
        if(get<1>(gameHandler.at(idx)) != nullptr && get<2>(gameHandler.at(idx)) != nullptr){
            if(get<1>(gameHandler.at(idx)) != ctc){
                emit get<1>(gameHandler.at(idx))->send_data(json_generator::opponent_leaved());
                get<1>(gameHandler.at(idx))->setInGame(false);
                get<1>(gameHandler.at(idx))->setGameId(-1);
            }else{
                emit get<2>(gameHandler.at(idx))->send_data(json_generator::opponent_leaved());
                get<2>(gameHandler.at(idx))->setInGame(false);
                get<2>(gameHandler.at(idx))->setGameId(-1);
            }
            return true;
        }
    }
    return false;
}

void Server::disconnectClient(ConnectionToClient * ctc){
    unsigned pos = 0;
    while(!(ctc == connections[pos])) {pos++;}
    connections.erase(connections.begin()+pos);
    removeLobby(ctc->getGameId());
    refreshLobbies();
    int idx = getIndexTuple(ctc);
    if (wasInGame(idx,ctc))
        removeTuple(idx);
    delete ctc;
}

void  Server::incomingConnection(qintptr handle){
    qDebug()<<"---------------------------------------\n"<<
              "New client coming with socket id "<< handle <<
              "\n----------------------------------------------\n";
    //new connection = new thread to handle the connection
    QThread * t = new QThread(this);
    ConnectionToClient * ctc = new ConnectionToClient(handle);
    ctc->moveToThread(t);
    ctc->setServer(this);
    ctc->setId(clientId);
    clientId++;
    //Once this thread is not used it flags it for deletion
    connect(t,SIGNAL(finished()),t,SLOT(deleteLater()));
    connections.push_back(ctc);
    //waits for the socket to get the connected status before notifying
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    notify_observers();
}

void Server::add_observer(Observer& observer)
{
    observers.push_back(&observer);
}

void Server::remove_observer(Observer& observer)
{
    observers.remove(&observer);
}

void Server::notify_observers()
{
    for(Observer* obs : observers)
    {
        obs->update();
    }
}


void Server::checkDbUser(QString pseudo){
    userRepository uRep;
    statRepository sRep;
    if(uRep.exist(pseudo.toStdString()) == 0){
        UserDto newUser = UserDto(pseudo.toStdString());
        StatDto newStat = StatDto(pseudo.toStdString(),0);
        uRep.add(newUser);
        sRep.add(newStat);
    }
}

bool Server::checkPauseDb(int gId, QString name){
    PauseRepository pRep;
    PauseDto res = pRep.select(name,gId);
    return res.getKey() != -1;
}

void Server::addGameToHistoryDb(const std::tuple<std::unique_ptr<Game>, ConnectionToClient *, ConnectionToClient *>& tuple){
    Game* g = get<0>(tuple).get();
    userRepository uRep;
    UserDto first = uRep.get(get<1>(tuple)->getPlayerPseudo().toStdString());
    UserDto second = uRep.get(get<2>(tuple)->getPlayerPseudo().toStdString());
    string winner = get<1>(tuple)->getPlayerPseudo().toStdString();
    if(g->get_winner() != get<1>(tuple)->getColor())
        winner = get<2>(tuple)->getPlayerPseudo().toStdString();
    HistoryDto hist = HistoryDto(first,second,winner);
    HistoryRepository hRep;
    hRep.add(hist);
}


void Server::addPauseToDb(QString name, int gameId){
    PauseRepository pRep;
    PauseDto item = PauseDto(name,gameId);
    pRep.add(item);
}

void Server::removePauseFromDb(QString name, int gId){
    PauseRepository pRep;
    pRep.deleteStmt(name,gId);
}

void Server::refreshStat(const std::tuple<std::unique_ptr<Game>, ConnectionToClient *, ConnectionToClient *>& tuple){
    Game* g = get<0>(tuple).get();
    if(g->get_winner() == get<1>(tuple)->getColor()){
        statRepository sRep;
        int nbVictory = sRep.getNbVictory(get<1>(tuple)->getPlayerPseudo().toStdString());
        StatDto dto = sRep.get(get<1>(tuple)->getPlayerPseudo().toStdString());
        dto.setNbVictory(nbVictory);
        get<1>(tuple)->setStat(nbVictory);
        sRep.update(dto);
    }else{
        statRepository sRep;
        int nbVictory = sRep.getNbVictory(get<2>(tuple)->getPlayerPseudo().toStdString());
        StatDto dto = sRep.get(get<2>(tuple)->getPlayerPseudo().toStdString());
        dto.setNbVictory(nbVictory);
        get<2>(tuple)->setStat(nbVictory);
        sRep.update(dto);
    }
}

Server::~Server(){
    QSqlQuery query = QSqlQuery("SELECT COUNT(*) FROM PAUSE");
    query.exec();
    query.first();
    int nb = query.value(0).toInt();
    query.clear();
    for(int i = 1 ; i <= nb ; i++){
        query = QSqlQuery("DELETE FROM PAUSE WHERE id="+QString::number(i));
        query.exec();
        query.first();
        query.clear();
    }
}
