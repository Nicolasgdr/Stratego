#ifndef DECK_H
#define DECK_H

#include <QWidget>
#include <QGridLayout>
#include <QPalette>
#include <QVariant>
#include "counter.h"
#include "../Stratego_libs/Model/game.h"
#include "convert.h"
#include "../Stratego_libs/Stratego-encap/json_interpreter.h"

/**
 * @brief The Deck class represents the deck of a player containing the pawns to place and the pawns
 * removed during the game (depending of the game state)
 */
class Deck : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Creates a new deck
     * @param parent The parent widget of the deck
     * @param color The color of the pawns contained in the deck.
     */
    Deck(QWidget * parent, Color color);

    /**
     * @brief Sets the game informations to display.
     * @param game The game informations
     */
    void setGame(game_info game);

    /**
     * @brief Update the display of the deck
     * @param state The current state of the game.
     * @param current The color of the player currently playing its turn.
     */
    void update(GameState state, Color current);

signals:
    void rank_selected(Rank rank);

private:
    const int COUNTER_WIDTH=120;
    const int COUNTER_HEIGHT=90;

    game_info game;
    Color color;
    Counter counters[RANK_NUMBER];
    QGridLayout layout =QGridLayout(this);
};

#endif // DECK_H
