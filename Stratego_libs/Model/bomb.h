#ifndef BOMB_H
#define BOMB_H

#include "piece.h"

/**
 * @brief A piece with rank Bomb.
 */
class Bomb : public Piece
{public :

    /**
     * @brief Builds up a new piece with rank Bomb, symbol "B"
     * and mobility false.
     * @param color The color of the piece.
     */
    Bomb(Color color);
};

#endif // BOMB_H
