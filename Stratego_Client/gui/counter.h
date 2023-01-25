#ifndef COUNTER_H
#define COUNTER_H

#include <QPushButton>
#include <QVBoxLayout>
#include "../Stratego_libs/Model/rank.h"

/**
 * @brief The Counter class represents a tile in the deck. Each counter
 * displays the number of pawns to place or removed depending of the game
 * state.
 */
class Counter : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief Creates a new counter
     * @param parent The parent widget of the counter.
     */
    Counter(QWidget * parent =nullptr);

    /**
     * @brief operator =
     * @param rhs
     */
    void operator = (Counter rhs);

    /**
     * @brief Swap the background of the counter. The background show's
     * which player as to play its turn.
     * @param colored Tells if the background must be colored (player's turns)
     * or if it must remain grey (other player's turn)
     */
    void swap_background(bool colored);

    /**
     * @brief Sets the number of pawns in the deck.
     * @param text The number of pawns.
     */
    void setText(QString text);

    /**
     * @brief Sets the default (grey) style of the counter visible and the
     * colored style hidden.
     * @param gray_url URL of the grey image.
     * @param colored_url URL of the colored image.
     */
    void default_style(QString gray_url, QString colored_url);

    /**
     * @brief Sets the size of background of the counter.
     */
    void set_fixed_size(int, int);

public slots:
signals:
    void clicked();

private:
    QVBoxLayout layout;
    QPushButton gray_background;
    QPushButton colored_background;

};

#endif // COUNTER_H
