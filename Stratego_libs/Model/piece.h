#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <iostream>
#include "color.h"
#include "rank.h"

/**
 * @brief The generic piece for the game.
 */
class Piece
{
    Color color;
    Rank rank;
    bool visibility;
    bool mobility;
    int nb;

public :

    /**
     * @brief Builds up a new piece.
     * @details Uses the given rank and color to build up a new piece.
     *  The visibility is false by default.
     * @param color The color of the piece.
     * @param rank The rank of the piece.
     * @param mobility If the piece can be moved, default: true.
     */
    Piece(Color color, Rank rank, bool mobility=true);

    /**
     * @brief Builds a copy of the given piece.
     * @param other A reference to the piece to copy.
     */
    Piece(const Piece& other);

    /**
     * @brief Builds a default piece.
     * @details The piece will be immobile with NONE color and EMPTY rank.
     */
    Piece();

    /**
     * @brief Gives the color of the piece.
     * @return The color of the piece.
     */
    Color get_color() const;

    /**
     * @brief Gives the rank of the piece.
     * @return The rank of the piece.
     */
    Rank get_rank() const;

    /**
     * @brief Gives the visibility of the piece, being hidden or not.
     * @return True if visible, else false.
     */
    bool get_visibility() const;

    /**
     * @brief Change the visibility of the piece.
     * @details Can be used for debug purpose (After a confrontation
     * between 2 pieces). Use during battle to see both pieces.
     * @param debug_mode If the debug_mode is true, the piece stay visible.
     */
    void flip_piece(bool debug_mode);

    /**
     * @brief The piece attacks the given piece.
     * @details The strongest piece, meaning the highest rank, win the battle.
     * If the rank of the two pieces is equal, both will be lost in battle.
     * During the confrontation, both pieces are visible.
     * @param other The defenser piece.
     * @return The pieces lost in the battle.
     */
    virtual std::vector<const Piece*> attack (const Piece& other) const;

    /**
     * @brief Return the mobility of the piece.
     * @return True if the piece is mobile, false otherwise.
     */
    virtual bool can_move() const;

    /**
     * @brief Check if the piece is able to move from start to end.
     * @details Do not verify if the two given positions exists or
     * if the path is free.
     * @param start_row The position's row where the piece come from.
     * @param start_col The position's column where the piece come from.
     * @param end_row The position's row toward which the piece is moved to.
     * @param end_col The position's column toward which the piece is moved to.
     * @return True if the move is possible, false otherwise.
     */
    virtual bool is_move_valid(int start_row, int start_col, int end_row, int end_col) const;

    /**
     * @brief Assign operator for a iece.
     * @details Copy the given piece into the one to be asigned.
     * @param rhs The piece to copy from.
     */
    void operator = (Piece rhs);

};

/**
 * @brief Less than operator between two pieces.
 * @details Compare the rank, depending of the
 * position in the enumeration.
 * @param lhs The left hand side piece to compare.
 * @param rhs The right hand side piece to compare.
 * @return True if the left hand side piece is less than
 * the right hand side one, false otherwise.
 */
bool operator < (const Piece& lhs, const Piece& rhs);

/**
 * @brief Equaly operator between two pieces.
 * @details Compare the rank and the color.
 * @param lhs The left hand side piece to check.
 * @param rhs The right hand side piece to check.
 * @return True if they are equals, else false.
 */
bool operator == (const Piece lhs, const Piece& rhs);

/**
 * @brief Different operator between two pieces.
 * @details Compare the rank, and the color.
 * @param lhs The left hand side piece to check.
 * @param rhs The right hand side piece to check.
 * @return True if they are different, else false.
 */
bool operator != (const Piece lhs, const Piece& rhs);

/**
 * @brief Insertion operator for a piece.
 * @param os The output stream into which insert the piece.
 * @param piece The piece to insert.
 * @return The output stream with piece's rank and color inserted.
 */
std::ostream& operator << ( std::ostream& os, Piece const& piece );

#endif // PIECE_H
