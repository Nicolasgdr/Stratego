#ifndef CASE_H
#define CASE_H

#include "piece.h"
#include <optional>

/**
 * @brief A position in the gameboard.
 */
class Case{

    int row;
    int col;
    Piece* piece_ptr;

public :

    /**
     * @brief Builds up a default position which row and column
     * equals -1.
     */
    Case();

    /**
     * @brief Builds up a new position.
     * @details Each position compose a part of the
     * gameboard. A position has a row and a column.
     * @param row The row of the position.
     * @param col The column of the position.
     */
    Case(int row, int col);

    /**
     * @brief Gives the row of the position.
     * @return The row of the position.
     */
    int getRow()const;

    /**
     * @brief Gives the column of the position.
     * @return The column of the position.
     */
    int getColumn()const;

    /**
     * @brief Gives the piece on the position.
     * @return The piece on the position, can return an EMPTY piece.
     */
    Piece& get_piece() const;

    /**
     * @brief Assign the given piece to the position.
     * @param piece The piece to set on the position.
     */
    void set_piece(Piece& piece);

    /**
     * @brief Flip the piece.
     * @details If the debug_mode is active, the piece remains permanently visible after
     * the first flip.
     * @param debug_mode The game's mode
     */
    void flip_piece(bool debug_mode);

    /**
     * @brief Removes the piece from the position.
     */
    void remove_Piece();

    /**
     * @brief Gives the color of the piece;
     * @return the color of the piece
     */
    Color get_piece_color();

    /**
     * @brief Check if the given position is a direct neighbor
     * of this position.
     * @details The neighbor must be row +1 or -1 with same
     * column or column +1 or -1 with the same row.
     * If the position is in diagonal neighborhood, it
     * is not considered as direct neighbor.
     * @param position The position to check.
     * @return True if the position is a direct neighbor,
     * else false.
     */
    bool is_neighbor(Case other);

    /**
     * @brief Check if another position is on the same row.
     * @param other The position to check.
     * @return True if on the same row, else false.
     */
    bool is_same_row(Case other);

    /**
     * @brief Check if another position is on the same column.
     * @param other Tthe position to check.
     * @return True if on the same column, else false.
     */
    bool is_same_column(Case other);

    /**
     * @brief Check if the position has a piece.
     * @return True if there is no piece on the position
     * else false.
     */
    bool is_empty();

};

/**
 * @brief Equaly operator between two positions.
 * @details Check if the row and column matches.
 * @param lhs, the left hand side position to check.
 * @param rhs, the right hand side position to check.
 * @return true if they are equals, else false.
 */
bool operator ==(const Case& lhs, const Case& rhs);

/**
 * @brief Different operator between two positions.
 * @details Check if the row and column are different.
 * @param lhs, the left hand side position to check.
 * @param rhs, the right hand side position to check.
 * @return true if they are different, else false.
 */
bool operator !=(const Case& lhs, const Case& rhs);

#endif // CASE_H
