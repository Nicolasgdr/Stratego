#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QVBoxLayout>

#include "../Stratego_libs/Stratego-encap/json_interpreter.h"
#include "welcome_home_page.h"
#include "listofgame.h"
#include "gui/graphicview.h"

/**
 * @brief The controller of the client part.
 */
class Client: public QWidget
{
    Q_OBJECT
public:
    /**
     * Creates the controller.
     * @brief Controller
     * @param parent
     */
    Client(QWidget *parent = nullptr);
    /**
     * @brief Sets the connection to the server (with its IP adress) and
     * shows the lobbies frame.
     */
    void player_click_start();

    /**
     * @brief Show the connection frame.
     */
    void start();

    /**
     * @brief Sets the player pseudo of this client.
     * @param pseudo The player's pseudonyme.
     */
    void set_pseudo(QString pseudo);

    /**
     * @brief Create a new game with given informations.
     * @param isPrivate Sets if the game is private (cannot be seen on the lobbies frame).
     * @param isAlone Sets if the player creates a solo game.
     * @param color Sets the color of the player creating the game.
     */
    void create_game(bool isPrivate, bool isAlone, Color color);

    /**
     * @brief Launch the game with second player's informations (joigning the game).
     * @param pseudo The pseudonyme of the second player.
     * @param gameId The gameID of the game he is joigning.
     * @param color The color of the second player.
     */
    void launch_game(QString pseudo, int gameId, Color color=NONE);

    /**
     * @brief Sets the turn to the next player.
     */
    void to_next_player();

    /**
     * @brief Sets the positions of a pawn during "PLACEMENT" game state.
     * @param row The row of the position where to place the pawn.
     * @param col The column of the position where to place the pawn.
     * @param rank The rank of the pawn.
     * @param color The color of the pawn.
     */
    void place_pawn(int row, int col, Rank rank, Color color);

    /**
     * @brief Change the position of a pown during "PLAYER_TURN" game state.
     * @param rowb The beginning's position row.
     * @param colb The beginning's position column.
     * @param rowe The ending's position row.
     * @param cole The ending's postion column.
     * @param color The color of the moving pawn.
     */
    void move_pawn(int rowb, int colb, int rowe, int cole, Color color);

    /**
     * @brief Delete a game.
     * @param gameId The gameID of the game to delete.
     */
    void delete_game(int gameId);

    /**
     * @brief Refresh the view to the lobbies frame.
     */
    void returning_to_lobby();

    /**
     * @brief Pause the game.
     */
    void pause();

    /**
     * @brief Reload a paused game.
     * @param id The gameID of the game to reload.
     */
    void reload_game(int id);

    /**
     * @brief Gets the pseudo of the player on this client.
     * @return The pseudo of the player.
     */
    QString get_player_pseudo();

    void setSoloGame(bool);

public slots:
    /**
     * Read the incomming information from the server
     * @brief read
     */
    void read();

private:

    QTcpSocket *socket;
    game_info game;
    QByteArray buffer;
    welcome_home_page *whp;
    ListOfGame *lg;
    GraphicView* gv;
    QString player_pseudo;
    QString current_player;
    void apply_server_action(QByteArray,Action_send);
    bool privateGame;
    bool soloGame;
    int idPartie;

    void setStyle();
};

#endif // CLIENT_H
