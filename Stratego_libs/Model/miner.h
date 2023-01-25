#ifndef MINER_H
#define MINER_H

#include "piece.h"

/**
 * @brief A piece with rank Miner.
 */
class Miner : public Piece
{public :

    /**
     * @brief Builds up a new piece with rank Miner and symbol "3".
     * @param color The color of the piece.
     */
    Miner(Color color);

    /**
     * @brief The piece attacks the given piece.
     * @details The strongest piece, meaning the highest rank, win the battle.
     * If the rank of the two pieces is equal, both will be lost in battle.
     * The miner win against bombs.
     * During the confrontation, both pieces are visible.
     * @param piece The defenser piece.
     * @return The pieces lost in the battle.
     */
    std::vector<const Piece*> attack (const Piece& other) const override;
};

#endif // MINER_H
