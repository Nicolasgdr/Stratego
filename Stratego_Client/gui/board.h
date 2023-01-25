#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <array>
#include "zone.h"
#include "tile.h"
#include "../Stratego_libs/Model/rank.h"
#include "convert.h"

using namespace std;

/**
 * @brief The Board class represent the view of the board.
 */
class Board : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Creates a new view of the stratego board.
     * @param parent The parent widget of the board.
     */
    Board(QWidget * parent);

    /**
     * @brief Updates the view with new board's informations.
     * @param new_board The board's informations to display.
     */
    void update(array<array<pair<Rank,Color>,10>,10> new_board);

signals:
    void pos_selected(int row, int col);

private:
    const int TILE_SIZE=65;

    Zone blue_zone;
    Zone central_zone;
    Zone red_zone;
    Tile tiles[10][10];
    QVBoxLayout layout=QVBoxLayout(this);

};

#endif // BOARD_H
