#ifndef ZONE_H
#define ZONE_H

#include <QWidget>
#include <QGridLayout>
#include "../Stratego_libs/Model/color.h"

/**
 * @brief The Zone class represents a zone of tile on the board.
 * There's 3 zones on the board : the blue zone, the red zone and the neutral zone.
 * The red zone allows red pawns to be placed.
 * The blue zone allows blue pawns to be placed.
 * The central zone allows none of the pieces to be placed.
 */
class Zone : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Creates a new zone.
     * @param parent The parent QWidget of the zone.
     * @param color The color of the zone (NONE if central zone).
     */
    Zone(QWidget * parent, Color color);

    /**
     * @brief Create a zone from other's zone informations
     * @param other The other zone.
     */
    Zone(Zone& other);

    /**
     * @brief operator = Redefinition for affectation.
     * @param rhs
     */
    void operator = (Zone rhs);

private:
    Color color;
    QGridLayout grid=QGridLayout(this);
};

#endif // ZONE_H
