#include "json_interpreter.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"

Rank json_interpreter::intToRank(int rank){
    Rank r;
    switch(rank){
        case 0: r = Rank::FLAG; break;
        case 1: r = Rank::SPY; break;
        case 2: r = Rank::SCOUT; break;
        case 3: r = Rank::MINER; break;
        case 4: r = Rank::SERGEANT; break;
        case 5: r = Rank::LIEUTENANT; break;
        case 6: r = Rank::CAPTAIN; break;
        case 7: r = Rank::MAJOR; break;
        case 8: r = Rank::COLONEL; break;
        case 9: r = Rank::GENERAL; break;
        case 10: r = Rank::MARSHAL; break;
        case 11: r = Rank::BOMB; break;
        case 13: r = Rank::UNKNOWN; break;
        case 14: r = Rank::WATER; break;
        default:
            r = Rank::EMPTY;
            break;
    }
    return r;
}

GameState json_interpreter::intToState(int state){
    GameState s;
    switch(state){
        case 1: s = GameState::PLACEMENT; break;
        case 2: s = GameState::PLAYER_TURN; break;
        case 3: s = GameState::NEXT_PLAYER; break;
        case 4: s = GameState::END_GAME; break;
        default:
            s = GameState::NOT_STARTED;
            break;
    }
    return s;
}

Action_send json_interpreter::intToAction(int r){
    Action_send a = ERROR;
    switch(r){
        case 0: a = Action_send::CONNECTION_TO_SERVER; break;
        case 1: a = Action_send::CREATE_GAME; break;
        case 2: a = Action_send::REFRESH_LOBBY; break;
        case 3: a = Action_send::LAUNCH_GAME; break;
        case 4: a = Action_send::SEND_DATA; break;
        case 5: a = Action_send::PLACE_PAWN; break;
        case 6: a = Action_send::MOVE_PAWN; break;
        case 7: a = Action_send::TO_NEXT_PLAYER; break;
        case 8: a = Action_send::GAME_IS_OVER; break;
        case 9: a = Action_send::ERROR; break;
        case 10: a = Action_send::PLACE_ALL_PAWN; break;
        case 11: a = Action_send::DELETE_GAME; break;
        case 12: a = Action_send::PRIVATE_GAME; break;
        case 13: a = Action_send::RETURNING_TO_LOBBY; break;
        case 14: a = Action_send::OPPONENT_LEAVED; break;
        case 15: a = Action_send::PAUSE; break;
        case 16: a = Action_send::GAME_PAUSE; break;
        case 17: a = Action_send::RELOAD_GAME; break;
    }
    return a;
}

QString json_interpreter::unpacked_connection_to_server(QByteArray data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    QString playerId = obj["PSEUDO"].toString();
    return playerId;
}

menu_info json_interpreter::unpacked_refresh_lobby(QByteArray data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    menu_info mi;
    mi.nbPlayers = obj["NB_PLAYERS"].toInt();
    mi.stat = obj["STAT"].toInt();
    QJsonArray lobbies = obj["LOBBIES"].toArray();
    for(unsigned i = 0 ; i < lobbies.size() ; i++){
        QJsonObject o = lobbies[i].toObject();
        lobby_info lobby;
        if(o["COLOR"].toInt() == 0)
            lobby.color = Color::RED;
        else
            lobby.color = Color::BLUE;
        lobby.creator = o["CREATOR"].toString();
        lobby.id_game = o["GAME_ID"].toInt();
        mi.lobbies.push_back(lobby);
    }
    return mi;
}

game_begin json_interpreter::unpacked_create_game(QByteArray data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    game_begin beginInfo;
    Color color = (obj["COLOR"].toInt() == 0) ? Color::RED : Color::BLUE;
    Player player = Player(obj["PSEUDO"].toString(),color);
    beginInfo.creator = player;
    beginInfo.isPrivate = obj["PRIVATE_GAME"].toBool();
    beginInfo.soloGame = obj["SOLO_GAME"].toBool();
    return beginInfo;
}

secondPlayerInfo json_interpreter::unpacked_launch_game(QByteArray data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    secondPlayerInfo info;
    Color color = Color::RED;
    if(obj["COLOR"].toInt() == 1) color = BLUE;
    else if(obj["COLOR"].toInt() == 3) color = NONE;
    Player player = Player(obj["PSEUDO"].toString(),color);
    info.player = player;
    info.gameId = obj["GAME_ID"].toInt();
    return info;
}

game_info json_interpreter::unpacked_send_data(QByteArray data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    game_info gi;
    gi.playerColor = (obj["PLAYER_COLOR"].toInt() == 0) ? Color::RED : Color::BLUE;
    gi.currentPlayerColor = (obj["CURRENT_PLAYER_COLOR"].toInt() == 0) ? Color::RED : Color::BLUE;
    gi.playerId = obj["PLAYER_ID"].toString();
    gi.state = intToState(obj["STATE"].toInt());

    QJsonArray piecesToPlace = obj["PIECES_TO_PLACE"].toArray();
    for(unsigned i = 0 ; i < piecesToPlace.size() ; i++){
        QJsonObject o = piecesToPlace[i].toObject();
        Rank rank = intToRank(o["RANK"].toInt());
        gi.piecesToPlaceLeft[i] = make_pair(o["NUMBER_LEFT"].toInt(), rank);
    }

    QJsonArray pawnPositions = obj["BOARD"].toArray();
    for(unsigned i = 0 ; i < pawnPositions.size() ; i++){
        QJsonObject o = pawnPositions[i].toObject();
        int x = o["ROW"].toInt();
        int y = o["COL"].toInt();
        Rank rank = intToRank(o["RANK"].toInt());
        Color color;
        if(o["COLOR"].toInt() == 0) color = Color::RED;
        else if(o["COLOR"].toInt() == 1) color = Color::BLUE;
        else color = Color::NONE;
        gi.board[x][y] = make_pair(rank,color);
    }

    QJsonArray removedPieces = obj["REMOVED_PIECES"].toArray();
    for(unsigned i = 0 ; i < removedPieces.size() ; i++){
        QJsonArray removedPiecesColor = removedPieces[i].toArray();
        for(unsigned j = 0 ; j < removedPiecesColor.size() ; j++){
            QJsonObject nb = removedPiecesColor[j].toObject();
            gi.removedPieces[i][j] = nb["NUMBER"].toInt();
        }
    }

    return gi;
}

placement json_interpreter::unpacked_place_pawn(QByteArray data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    placement p;
    p.player_color = (obj["COLOR"] == 0) ? Color::RED : Color::BLUE;
    p.position = Case(obj["ROW"].toInt(),obj["COL"].toInt());
    p.rank = intToRank(obj["RANK"].toInt());
    return p;
}

moveInfo json_interpreter::unpacked_move_pawn(QByteArray data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    moveInfo mi;
    mi.currentPlayerCol = (obj["COLOR"].toInt() == 0) ? Color::RED : Color::BLUE;
    mi.begin = Case(obj["START_ROW"].toInt(),obj["START_COL"].toInt());
    mi.end = Case(obj["END_ROW"].toInt(),obj["END_COL"].toInt());
    return mi;
}

QString json_interpreter::unpacked_game_is_over(QByteArray data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    QString winner = "The game is a draw.";
    if(obj["COLOR"].toInt() == 0){
        winner = "Congratulations red player has won.";
    }else if(obj["COLOR"].toInt() == 1){
        winner = "Congratulations blue player has won.";
    }
    return winner;
}

QString json_interpreter::unpacked_error(QByteArray data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    return obj["MESSAGE"].toString();
}

Action_send json_interpreter::get_type(QByteArray data)
{
    QJsonDocument document = QJsonDocument::fromJson(data);
    Action_send msg;
    QJsonObject object = document.object();
    msg = intToAction(object["TYPE_MSG"].toInt());
    return msg;
}

int json_interpreter::unpacked_private_game(QByteArray data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    return obj["GAME_ID"].toInt();
}

place_file json_interpreter::unpacked_place_all_pawn(QByteArray data){
    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonObject obj = document.object();
    place_file fileinfo;

    QJsonArray pawnPositions = obj["BOARD"].toArray();
    for(unsigned i = 0 ; i < pawnPositions.size() ; i++){
        QJsonObject o = pawnPositions[i].toObject();
        int x = o["ROW"].toInt();
        int y = o["COL"].toInt();
        Rank rank = intToRank(o["RANK"].toInt());
        Color color;
        if(obj["COLOR"].toInt() == 0) color = Color::RED;
        else if(obj["COLOR"].toInt() == 1) color = Color::BLUE;
        else color = Color::NONE;
        fileinfo.board[x][y] = make_pair(rank,color);
    }
    return fileinfo;
}

int json_interpreter::unpacked_game_pause(QByteArray data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    return obj["GAME_ID"].toInt();
}

int json_interpreter::unpacked_reload_game(QByteArray data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    return obj["GAME_ID"].toInt();
}
