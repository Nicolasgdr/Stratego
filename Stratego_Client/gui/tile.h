#ifndef TILE_H
#define TILE_H

#include <QPushButton>
#include <QMouseEvent>
#include <array>

/**
 * @brief The Tile class represents a tile on the view.
 */
class Tile : public QPushButton
{
    Q_OBJECT

public:
    /**
     * @brief Creates a new tile
     * @param parent The parent widget of the tile
     */
    Tile(QWidget * parent =nullptr);

    /**
     * @brief Creates a new tile with another tile attributes.
     * @param other The other tile
     */
    Tile(Tile& other);

    /**
     * @brief operator = Redefinition for affectation.
     * @param rhs
     */
    void operator = (Tile rhs);


private:
    void clickEvent(QMouseEvent*);
};

#endif // TILE_H
