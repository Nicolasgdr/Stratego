#ifndef LISTOFGAME_H
#define LISTOFGAME_H

#include <QWidget>
#include "case_lobby.h"
#include "../Stratego_libs/Model/color.h"

//fwd declaration
class Client;
struct lobby_info;

namespace Ui {
class ListOfGame;
}

/**
 * @brief Class of the lobbies view.
 */
class ListOfGame : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Creates a new lobbies frame.
     * @param parent The parent Widget of the lobbies frame.
     * @param cli The controller for the client.
     */
    explicit ListOfGame(QWidget *parent = nullptr, Client* cli = nullptr);

    /**
     * @brief Display the lobbies frame.
     */
    void showListOfGame();

    /**
     * @brief Refresh the view (Public lobbies, number of players online and player victories)
     * @param lobbies The public lobbies accesible on the frame.
     * @param nbPlayers The numbre of player curretly connected.
     * @param stat The victory statistics of the player.
     */
    void refresh(std::vector<lobby_info> lobbies, int nbPlayers, int stat);

    /**
     * @brief Display, for a brief moment, a message box giving the gameID of the private game
     * freshly created.
     * @param gameId The gameID of the private game.
     */
    void showPrivateGame(int gameId);

    /**
     * @brief Display a message box giving the reason of an error.
     * @param msg The error message to display
     */
    void showError(QString msg);

    /**
     * @brief Enable the "create game" button.
     */
    void enableCreateButton();

private slots:
    void on_NewGameButton_clicked();

    void on_clicked_item(QListWidgetItem* item);

    void on_join_clicked();

    void on_reload_game_clicked();

    void on_Button_private_toggled(bool checked);

    void on_Button_solo_toggled(bool checked);

private:

    Ui::ListOfGame *ui;
    Client * cli;
};

#endif // LISTOFGAME_H
