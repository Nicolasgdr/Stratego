#include "Client.h"
#include "QHostAddress"
#include "../Stratego_libs/Stratego-encap/json_generator.h"
#include <iostream>
#include <thread>

Client::Client(QWidget *parent): QWidget(parent), player_pseudo("player"), soloGame(false)
{
    socket = new QTcpSocket();
    this->whp = new welcome_home_page(this,this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(read()),Qt::DirectConnection);
    setStyle();
}

void Client::setStyle()
{
    QPixmap pixmap;
    pixmap.load("../Stratego_Client/img/icon.jpg");
    QIcon icon(pixmap);
    this->setWindowIcon(icon);
    this->setWindowTitle("Stratego");
    this->setFixedSize(1190,700);
}

void Client::start(){
    this->whp->show_welcome_gui();
}

void Client::set_pseudo(QString pseudo){
    player_pseudo = pseudo;
}


void Client::create_game(bool isPrivate, bool isAlone, Color color){
    soloGame = isAlone;
    socket->write(json_generator::create_game(player_pseudo,color,isAlone,isPrivate));
}

void Client::launch_game(QString pseudo, int gameId, Color color){
    socket->write(json_generator::launch_game(pseudo,gameId,color));
}

void Client::to_next_player(){
    socket->write(json_generator::next_player());
}

void Client::place_pawn(int row, int col, Rank rank, Color color){
    socket->write(json_generator::place_pawn(row,col,color,rank));
}

void Client::move_pawn(int rowb, int colb, int rowe, int cole, Color color){
    socket->write(json_generator::move_pawn(rowb,colb,rowe,cole,color));
}

void Client::delete_game(int gameId){
    socket->write(json_generator::delete_game(gameId));
}

void Client::returning_to_lobby(){
    socket->write(json_generator::returning_to_lobby());
}

void Client::pause(){
    if(soloGame)
        socket->write(json_generator::pause());
}

void Client::reload_game(int id){
    socket->write(json_generator::reload_game(id));
}

QString Client::get_player_pseudo(){
    return player_pseudo;
}

void Client::setSoloGame(bool b){
    soloGame = b;
}

void Client::player_click_start()
{
    socket->connectToHost("127.0.0.1",2022);
    if(socket->isOpen()){
        socket->write(json_generator::connection_to_server(player_pseudo));
    }
    lg = new ListOfGame(this,this);
    lg->showListOfGame();
}


void Client::read(){
    qDebug() << "---------------------------\n"<<"Data received...\n";
    qDebug()<<"available bytes"<<socket->bytesAvailable();
    buffer.clear();
    QDataStream stream(socket);
    stream.startTransaction();
    stream >> buffer;
    stream.commitTransaction();
    qDebug()<<buffer;
    Action_send type = json_interpreter::get_type(buffer);
    QJsonDocument doc = QJsonDocument::fromJson(buffer);
    qDebug() << doc;
    qDebug()<<type;
    apply_server_action(buffer,type);
}

void Client::apply_server_action(QByteArray data,Action_send action)
{
    switch (action) {
    case SEND_DATA:{
        if(!gv){
            gv = (soloGame) ? new GraphicView(true,this,this) : new GraphicView(false,this,this);
            gv->showGame();
        }
        this->game = json_interpreter::unpacked_send_data(data);
        qDebug()<<"send data";
        this->current_player = this->game.playerId;
        gv->setGame(game);
        break;
    }
    case GAME_IS_OVER:{
        if(gv) {
            gv->showEndGame(json_interpreter::unpacked_game_is_over(data));
            gv->hide();
            gv = nullptr;
            soloGame = false;
            if(lg) {
                lg->enableCreateButton();
                lg->showListOfGame();
            }
        }
        break;
    }
    case REFRESH_LOBBY:{
        menu_info mi = json_interpreter::unpacked_refresh_lobby(data);
        lg->refresh(mi.lobbies, mi.nbPlayers,mi.stat);
        break;
    }
    case ERROR :{
        if(gv){ gv->showError(json_interpreter::unpacked_error(data));}
        else if(lg) {lg->showError(json_interpreter::unpacked_error(data));}
        break;
    }
    case PRIVATE_GAME:{
        qDebug()<<"private game";
        if (lg)
            lg->showPrivateGame(json_interpreter::unpacked_private_game(data));
        break;
    }
    case OPPONENT_LEAVED:{
        qDebug()<<"opponent leaved";
        if(gv){
            gv->hide();
            gv = nullptr;
            if(lg) {
                lg->enableCreateButton();
                lg->showListOfGame();
                lg->showError("Your opponent leaved the game.");
            }
        }
        break;
    }
    case GAME_PAUSE:{
        qDebug()<<"making a pause";
        if(gv){
            gv->showMessage(json_interpreter::unpacked_game_pause(data));
            gv->hide();
            gv = nullptr;
            soloGame = false;
            if(lg) {
                lg->enableCreateButton();
                lg->showListOfGame();
            }
        }
        break;
    }
    default:
        qDebug()<<"this is default";
        break;
    }
}
