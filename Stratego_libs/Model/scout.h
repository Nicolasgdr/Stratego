#ifndef SCOUT_H
#define SCOUT_H

#include "piece.h"

/**
 * @brief A piece with rank Scout.
 */
class Scout : public Piece
{public :

    /**
     * @brief Builds up a new piece with rank Scout and symbol "2".
     * @param color The color of the piece.
     */
    Scout(Color color);

    /**
     * @brief Check if the given positions share the same row or
     * the same column.
     * @details Do not verify if the two given positions exists or
     * if the path is free.
     * @param start The position where the piece come from.
     * @param end The position toward which the piece is moved to.
     * @return True if the move is possible, false otherwise.
     */
    bool is_move_valid(int start_row, int start_col, int end_row, int end_col) const override;
};

#endif // SCOUT_H
