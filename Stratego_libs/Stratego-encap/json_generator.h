#ifndef JSON_GENERATOR_H
#define JSON_GENERATOR_H
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"
#include "../Model/game.h"
#include "../Model/action_send.h"
#include "json_interpreter.h"


class json_generator
{
    static bool is_file_correct(string file_path);
    static Rank symbol_to_rank(string symbol);

public:
    json_generator()=default;

    /**
     * @brief CONNECTION_TO_SERVER will generate the json send to the server
     * by the client to be connected
     * @return json
     */
    static QByteArray connection_to_server(QString pseudo);
    /**
     * @brief CREATE_GAME will generate the json send to the server
     * by the client to create the game
     * @return json
     */
    static QByteArray create_game(QString pseudo,Color color,bool soloGame, bool privateGame);
    /**
     * @brief REFRESH_LOBBY will generate the json send to the client
     * by the server to refresh the different game available for the player
     * @return json
     */
    static QByteArray refresh_lobby(std::vector<std::tuple<int, QString, Color>> lobbiesInfo, int nbPlayers, int stat);
    /**
     * @brief LAUNCH_GAME will generate the json send to the server
     * by the client to start the game and ask the view
     * @return json
     */
    static QByteArray launch_game(QString pseudo, int idPartie, Color color = NONE);

    /**
     * @brief SEND_DATA will generate the json send to the client
     * by the server to update the view of the game
     * @return json
     */
    static QByteArray send_data(Game* g, Color player_color, QString playerIdc);
    /**
     * @brief PLACE_PAWN  will generate the json send to the server
     * by the client to place a pawn during the game
     * @return json
     */
    static QByteArray place_pawn(int row, int col, Color color_player, Rank rank);
    /**
     * @brief MOVE_PAWN  will generate the json send to the server
     * by the client tomove a pawn during the game
     * @return json
     */
    static QByteArray move_pawn(int rowbegin, int colbegin,int rowend, int colend, Color color_player);

    static QByteArray next_player();
    /**
     * @brief GAME_IS_OVER will generate the json send to the client
     * by the server
     * @return json
     */
    static QByteArray game_is_over(Color color);
    /**
     * @brief INVALID_MOVE will generate the json send to the client
     * by the server, send an error message in the view
     * @return json
     */
    static QByteArray error(QString message);

    static QByteArray delete_game(int gameId);

    static QByteArray private_game(int gameId);
    /**
     * @brief place_all_pawn take the file of all position and send it to the server
     * to place all pawn on my side
     * @return json
     */
    static QByteArray place_all_pawn(string file_path, Color player_color);

    static QByteArray returning_to_lobby();

    static QByteArray opponent_leaved();

    static QByteArray pause();

    static QByteArray game_pause(int gameId);

    static QByteArray reload_game(int gameId);
};

#endif // JSON_GENERATOR_H
