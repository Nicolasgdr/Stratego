#ifndef SPY_H
#define SPY_H

#include "piece.h"

/**
 * @brief A piece with rank Spy.
 */
class Spy : public Piece
{public :

    /**
     * @brief Builds up a new piece with rank Spy and symbol "1".
     * @param color The color of the piece.
     */
    Spy(Color color);

    /**
     * @brief The piece attacks the given piece.
     * @details The strongest piece, meaning the highest rank, win the battle.
     * If the rank of the two pieces is equal, both will be lost in battle.
     * The spy wins against the marshal if attacking (loses in the other way).
     * During the confrontation, both pieces are visible.
     * @param piece The defenser piece.
     * @return The pieces lost in the battle.
     */
    std::vector<const Piece*> attack (const Piece& other) const override;
};

#endif // SPY_H
