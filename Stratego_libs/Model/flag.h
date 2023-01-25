#ifndef FLAG_H
#define FLAG_H

#include "piece.h"

/**
 * @brief A piece with rank Flag.
 */
class Flag : public Piece
{public :

    /**
     * @brief Builds up a new piece with rank Flag, symbol "F"
     * and mobility false.
     * @param color The color of the piece.
     */
    Flag(Color color);
};

#endif // BOMB_H
