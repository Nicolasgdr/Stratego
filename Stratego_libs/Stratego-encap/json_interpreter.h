#ifndef JSON_INTERPRETER_H
#define JSON_INTERPRETER_H

#include "../Model/color.h"
#include <array>
#include "QString"
#include "../Model/game.h"
#include "../Model/action_send.h"

/**
 * @brief The game_info class
 * c'est les différents variable qui seront remplis pour savoir l'etat
 * du board
 */
struct game_info{
    Color currentPlayerColor;
    Color playerColor;
    GameState state;
    QString playerId;
    array<pair<int,Rank>,Rank::RANK_NUMBER> piecesToPlaceLeft;
    array<array<pair<Rank, Color>,10>,10> board;
    array<array<int,RANK_NUMBER>, COLOR_NUMBER> removedPieces;
};

struct game_begin{
    bool isPrivate;
    Player creator;
    bool soloGame;
};

struct lobby_info{
    //liste de game --> avec le bouton
    QString creator;
    //the other color
    Color color;
    unsigned id_game;
};

struct menu_info{
    int nbPlayers;
    int stat;
    std::vector<lobby_info> lobbies;
};

struct secondPlayerInfo{
    Player player;
    int gameId;
};

/**
 * @brief The placement class
 * variable pour une case précise
 */
struct placement{
    Case position;
    Color player_color;
    Rank rank;
};

struct place_file{
     array<array<pair<Rank, Color>,10>,10> board;
};

struct moveInfo{
    Case begin;
    Case end;
    Color currentPlayerCol;
};

class json_interpreter
{

public:
    json_interpreter() = default;

    static Rank intToRank(int rank);

    static GameState intToState(int state);

    static Action_send intToAction(int msg);
    /**
     * @brief Contains the id of the player that is represented through a pseudonym.
     * @param data the data to unpack
     * @return the id of the player
     */
    static QString unpacked_connection_to_server(QByteArray data);

    /**
     * @brief Contains information about the menu that is showed after the connection.
     * @param data the list of lobbies and the number of connected clients
     * @return menu_info the menu informations
     */
    static menu_info unpacked_refresh_lobby(QByteArray data);

    /**
     * @brief Contains information to create a game.
     * The creator, the selected color, if the game is private and if playing
     * against a bot.
     * @param data the information to create a game
     * @return a structure that contains the information to create a game.
     */
    static game_begin unpacked_create_game(QByteArray data);

    /**
     * @brief Contains information about the second player that is joining a game.
     * @param data information of the player and the game.
     * @return a structure that contains information of the player joining game
     */
    static secondPlayerInfo unpacked_launch_game(QByteArray data);

    /**
     * @brief Contains information about the board.
     * @param data information of the board
     * @return a structure that contains information of the board
     */
    static game_info unpacked_send_data(QByteArray data);

    /**
     * @brief Contains information about a pawn placement.
     * It contains the Case where the client wants to put the pawn.
     * @param data the data to place the pawn
     * @return placement information
     */
    static placement unpacked_place_pawn(QByteArray data);

    /**
     * @brief Contains the information about a pawn move.
     * It contains the beginning and the end positions of the pawn, its rank and
     * the colour of the current player that is moving the pawn.
     * @param data the data to move the pawn
     * @return the information about the moving pawn
     */
    static moveInfo unpacked_move_pawn(QByteArray data);

    /**
     * @brief Contains the information about the winner.
     * @return the winner
     */
    static QString unpacked_game_is_over(QByteArray data);


    static QString unpacked_error(QByteArray data);

    /**
     * @brief Gets the type of message that is sended.
     * @return the type of the message
     */
    static Action_send get_type(QByteArray);

    static int unpacked_private_game(QByteArray data);
    /**
     * @brief unpacked_place_all_pawn
     * @return all the pawn to be place
     */
    static place_file unpacked_place_all_pawn(QByteArray);

    static int unpacked_game_pause(QByteArray);

    static int unpacked_reload_game(QByteArray);
};

#endif // JSON_INTERPRETER_H
