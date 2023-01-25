#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <exception>
#include "board.h"
#include "deck.h"
#include "buffer.h"
#include "../Stratego_libs/Stratego-encap/json_interpreter.h"

class Client;

using namespace cvrt;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

/**
 * @brief Class of the game frame
 */
class GraphicView : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief Creates a new game frame.
     * @param solo Define if this is a solo game.
     * @param parent The parent widget of the game frame
     * @param cli The cotroller of the client.
     */
    GraphicView(bool solo, QWidget *parent = nullptr, Client* cli = nullptr);

    ~GraphicView();

    /**
     * @brief Sets the game information used for the frame refreshment.
     * @param game The game informations.
     */
    void setGame(game_info game);

    /**
     * @brief Updates the view.
     */
    void update();

    /**
     * @brief Show the game frame.
     */
    void showGame();

    /**
     * @brief Displays an error occuring in a message box
     * @param msg The error message to display
     */
    void showError(QString msg);

    /**
     * @brief Displays a message with the game's winner color
     * @param msg The message to display.
     */
    void showEndGame(QString msg);

    /**
     * @brief Displays a message for the game
     * @param nb The gameID
     */
    void showMessage(int nb);

public slots:

    /**
     * @brief Receive rank's information to transfer.
     * @param rank The rank information
     */
    void give_info(Rank rank);

    /**
     * @brief Receive a position's information to transfer.
     * Depending on the game state, this position can be used to
     * place a pawn or the move a pawn. It can be used with a position
     * store in the buffer to move a pawn.
     * @param row The row of the position
     * @param col The column of the position.
     */
    void give_info(int row, int col);

    /**
     * @brief Change the player currently playing and update the view
     * if the game is over.
     */
    void next_player();

    /**
     * @brief Pause the game.
     */
    void do_pause();

signals:
    void taskFinished();

private:
    Client* cli;
    game_info game;
    Board board;
    Deck blue_deck;
    Deck red_deck;
    QPushButton player;
    QPushButton pause;
    bool soloGame;

    QWidget widget = QWidget(this);
    QHBoxLayout hbox= QHBoxLayout(&widget);
    QVBoxLayout decks_layout;
    QHBoxLayout buttons_layout;

    Buffer buffer;

    Ui::Widget *ui;

    void initlayouts();
    void initBoard();
    void initDecks();
    void initPlayer();
    void initPause();
    void initConnections();
    void placement();
};
#endif // GRAPHICVIEW_H
