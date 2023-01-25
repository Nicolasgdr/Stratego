#include "json_generator.h"

QByteArray json_generator::connection_to_server(QString pseudo){
    QJsonObject json_player;
    json_player.insert("TYPE_MSG",Action_send::CONNECTION_TO_SERVER);
    json_player.insert("PSEUDO",pseudo);
    return QJsonDocument(json_player).toJson();
}

QByteArray json_generator::create_game(QString pseudo, Color color, bool soloGame, bool privateGame){
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",Action_send::CREATE_GAME);
    json_ob.insert("PSEUDO",pseudo);
    json_ob.insert("COLOR",color);
    json_ob.insert("SOLO_GAME",soloGame);
    json_ob.insert("PRIVATE_GAME",privateGame);
    return QJsonDocument(json_ob).toJson();
}

QByteArray json_generator::refresh_lobby(std::vector<std::tuple<int, QString, Color>> lobbiesInfo, int nbPlayers, int stat){
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",Action_send::REFRESH_LOBBY);
    json_ob.insert("NB_PLAYERS",nbPlayers);
    json_ob.insert("STAT",stat);
    QJsonArray lobbies;
    for(unsigned i = 0 ; i < lobbiesInfo.size() ; i++){
        std::tuple<int,QString,Color> lobbyInfo = lobbiesInfo[i];
        QJsonObject lobby;
        lobby["GAME_ID"] = get<0>(lobbyInfo);
        lobby["CREATOR"] = get<1>(lobbyInfo);
        lobby["COLOR"] = get<2>(lobbyInfo);
        lobbies.push_back(lobby);
    }
    json_ob.insert("LOBBIES",lobbies);
    return QJsonDocument(json_ob).toJson();
}

QByteArray json_generator::launch_game(QString pseudo, int idPartie, Color color){
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",Action_send::LAUNCH_GAME);
    json_ob.insert("PSEUDO",pseudo);
    json_ob.insert("COLOR",color);
    json_ob.insert("GAME_ID",idPartie);
    return QJsonDocument(json_ob).toJson();
 }

QByteArray json_generator::send_data(Game* g, Color player_color,QString playerId){

    int height  = (g->get_board(player_color).size());
    int width = (g->get_board(player_color).size());
    Rank rank_temp;
    Color color_temp;
    QJsonObject json_object;
    json_object.insert("TYPE_MSG",Action_send::SEND_DATA);
    json_object.insert("PLAYER_COLOR",player_color);
    json_object.insert("CURRENT_PLAYER_COLOR",g->get_current_player());
    json_object.insert("PLAYER_ID",playerId);
    json_object.insert("STATE", g->get_state());

    if(g->get_state() == GameState::PLACEMENT){
        QJsonArray piecesToPlace;
        for(unsigned r = 0 ; r < Rank::RANK_NUMBER ; r++){
            QJsonObject piece;
            Rank rank = json_interpreter::intToRank(r);
            piece["RANK"] = QJsonValue((int)r);
            piece["NUMBER_LEFT"] = g->get_pieces_to_place_left(rank, player_color);
            piecesToPlace.push_back(piece);
        }
        json_object.insert("PIECES_TO_PLACE",piecesToPlace);
    }

    if(g->get_state() == GameState::PLAYER_TURN || g->get_state() == GameState::NEXT_PLAYER){
        array<array<int,RANK_NUMBER>, COLOR_NUMBER> removedPiecesInfo = g->get_removed_pieces();
        QJsonArray removedPieces;
        for(unsigned color = 0 ; color < Color::COLOR_NUMBER ; color++){
            QJsonArray removedPiecesColor;
            for(unsigned rank = 0 ; rank < Rank::RANK_NUMBER ; rank++){
                QJsonObject piece;
                piece["NUMBER"] = removedPiecesInfo[color][rank];
                removedPiecesColor.push_back(piece);
            }
            removedPieces.push_back(removedPiecesColor);
        }
        json_object.insert("REMOVED_PIECES",removedPieces);
    }

    if(g->get_state() != END_GAME){
        QJsonArray data;
        for (int row=0;row<height ;row++ ) {
            for(int col=0;col<width;col++)
            {
                QJsonObject case_;
                rank_temp = g->get_board(player_color)[row][col].first;
                color_temp = g->get_board(player_color)[row][col].second;
                case_.insert("ROW",row);
                case_.insert("COL",col);
                case_.insert("RANK",rank_temp);
                case_.insert("COLOR",color_temp);
                data.push_back(case_);
            }
        }
        json_object.insert("BOARD",data);
    }

    return QJsonDocument(json_object).toJson(QJsonDocument::Indented);
 }

QByteArray json_generator::place_pawn(int row,int col, Color color, Rank rank){
    QJsonObject obj;
    obj.insert("TYPE_MSG",Action_send::PLACE_PAWN);
    obj.insert("ROW",row);
    obj.insert("COL",col);
    obj.insert("COLOR",color);
    obj.insert("RANK",rank);
    return QJsonDocument(obj).toJson();
 }

QByteArray json_generator::move_pawn(int rowbegin, int colbegin,int rowend, int colend, Color color){
    QJsonObject obj;
    obj.insert("TYPE_MSG",Action_send::MOVE_PAWN);
    obj.insert("START_ROW",rowbegin);
    obj.insert("START_COL",colbegin);
    obj.insert("END_ROW",rowend);
    obj.insert("END_COL",colend);
    obj.insert("COLOR",color);
    return QJsonDocument(obj).toJson();
 }

QByteArray json_generator::next_player(){
    QJsonObject colorWinner;
    colorWinner.insert("TYPE_MSG",Action_send::TO_NEXT_PLAYER);
    return QJsonDocument(colorWinner).toJson();
}

QByteArray json_generator::game_is_over(Color color){
    QJsonObject colorWinner;
    colorWinner.insert("TYPE_MSG",Action_send::GAME_IS_OVER);
    colorWinner.insert("COLOR",color);
    return QJsonDocument(colorWinner).toJson();
 }

QByteArray json_generator::error(QString message){
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",Action_send::ERROR);
    json_ob.insert("MESSAGE",message);
    return QJsonDocument(json_ob).toJson();
 }

QByteArray json_generator::delete_game(int gameId){
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",Action_send::DELETE_GAME);
    json_ob.insert("GAME_ID",gameId);
    return QJsonDocument(json_ob).toJson();
}

QByteArray json_generator::private_game(int gameId){
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",Action_send::PRIVATE_GAME);
    json_ob.insert("GAME_ID",gameId);
    return QJsonDocument(json_ob).toJson();
}

QByteArray json_generator::place_all_pawn(string file_path, Color player_color){
    QJsonObject obj;
    obj.insert("TYPE_MSG",Action_send::PLACE_ALL_PAWN);

    ifstream ifs;
    ifs.open(file_path);
    if(!ifs.is_open())
        throw invalid_argument("Cannot open the path");
    ifs.close();
    if(!is_file_correct(file_path))
        throw domain_error("Invalid format for pieces placement");
    ifs.open(file_path, ios::in);

    string symbol;

    for(unsigned file_row=0; file_row<4; file_row++)
    {
        for(int col=0; col<10; col++){
            if(col<9) getline(ifs,symbol,' ');
            else getline(ifs,symbol);

            //if RED, place from row 9 to row 6
            //if BLUE, place from row 0 to row 3
            int board_row = (player_color==RED) ? 9-file_row : file_row;

            obj.insert("ROW",board_row);
            obj.insert("COL",col);
            obj.insert("COLOR",player_color);
            obj.insert("RANK",symbol_to_rank(symbol));
        }
    }

    ifs.close();
    return QJsonDocument(obj).toJson();
}

bool json_generator::is_file_correct(string file_path)
{
    ifstream file;
    file.open(file_path);
    bool is_correct = file.is_open();
    array<int,12> piecesToPlace = {1,1,8,5,4,4,4,3,2,1,1,6};

    string symbol;
    unsigned symbol_cpt=0;
    unsigned row_cpt=0;
    unsigned col_cpt;
    int rank_cpt[RANK_NUMBER]{};
    while(is_correct && row_cpt<4 && symbol_cpt<40)
    {
        col_cpt=0;
        while(is_correct && col_cpt<10 && symbol_cpt<40)
        {
            if(col_cpt<9) getline(file,symbol,' ');
            else getline(file,symbol);          // End of line
            Rank rank=symbol_to_rank(symbol);
            is_correct &= rank!=UNKNOWN;
            if(is_correct)
            {
                rank_cpt[rank]++;
                symbol_cpt++;
                is_correct &= rank_cpt[rank]<= piecesToPlace[rank];
            }
            col_cpt++;
        }

        row_cpt++;

    }

    is_correct &= symbol_cpt==40 && row_cpt==4 && col_cpt==10;

    file.close();
    return is_correct;
}

Rank json_generator::symbol_to_rank(string symbol)
{
    if(symbol=="F" || symbol=="f" || symbol=="D" || symbol=="d") return FLAG;
    else if(symbol=="1") return SPY;
    else if(symbol=="2") return SCOUT;
    else if(symbol=="3") return MINER;
    else if(symbol=="4") return SERGEANT;
    else if(symbol=="5") return LIEUTENANT;
    else if(symbol=="6") return CAPTAIN;
    else if(symbol=="7") return MAJOR;
    else if(symbol=="8") return COLONEL;
    else if(symbol=="9") return GENERAL;
    else if(symbol=="10") return MARSHAL;
    else if(symbol=="B" || symbol=="b") return BOMB;
    else return UNKNOWN;
}

QByteArray json_generator::returning_to_lobby(){
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",Action_send::RETURNING_TO_LOBBY);
    return QJsonDocument(json_ob).toJson();
}

QByteArray json_generator::opponent_leaved(){
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",Action_send::OPPONENT_LEAVED);
    return QJsonDocument(json_ob).toJson();
}

QByteArray json_generator::pause(){
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",Action_send::PAUSE);
    return QJsonDocument(json_ob).toJson();
}


QByteArray json_generator::game_pause(int gameId){
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",Action_send::GAME_PAUSE);
    json_ob.insert("GAME_ID",gameId);
    return QJsonDocument(json_ob).toJson();
}


QByteArray json_generator::reload_game(int gameId){
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",Action_send::RELOAD_GAME);
    json_ob.insert("GAME_ID",gameId);
    return QJsonDocument(json_ob).toJson();
}
