#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <array>
#include <list>
#include "case.h"
#include "flag.h"
#include "spy.h"
#include "scout.h"
#include "miner.h"
#include "bomb.h"

using namespace std;

/**
 * @brief The board of the game.
 * @details Contains and updates the board of the game, the lists of both
 * dead and alive pieces, the flags and check the last moves of each player.
 */
class Gameboard
{
    const static unsigned WIDTH=10;
    const static unsigned HEIGHT=10;
    constexpr static array<int,RANK_NUMBER> MULTIPLICITIES={1,1,8,5,4,4,4,3,2,1,1,6};

    array<list<pair<Case,Piece>>,COLOR_NUMBER> last_positions;
    array<array<int,RANK_NUMBER>,COLOR_NUMBER> removed_pieces;
    array<array<Case,WIDTH>,HEIGHT> cases;
    array<array<list<Piece>,RANK_NUMBER>,COLOR_NUMBER> regular_pieces;
    array<list<Flag>,COLOR_NUMBER> flags;
    array<list<Spy>,COLOR_NUMBER> spies;
    array<list<Scout>,COLOR_NUMBER> scouts;
    array<list<Miner>,COLOR_NUMBER> miners;
    array<list<Bomb>,COLOR_NUMBER> bombs;


    void add_last_move(const Case& position, Color color);

    bool is_path_free(Case& start, Case& end);

    void battle(Case& start, Case& end, bool debug_mode);

    void move(Case& start, Case& end);

    void flip(Case& pos, bool debug_mode);

public:

    /**
     * @brief Builds up a new gameboard.
     * @details Initialises the board and the required elements for the game.
     */
    Gameboard();

    /**
     * @brief Check if the board contains the given position.
     * @param position The position which is verified.
     * @return True if the board contains the position, false otherwise.
     */
    bool contain(Case position);


    /**
     * @brief Move the piece from start to end.
     * @details If the end position is already used by an other player's piece,
     * does the battle between them. If the start position is empty, if one or
     * both the positions does not exist or if the end position is occupied by
     * a piece of the same color, the comportement is undefined.
     * @param start_row The position's row where is the moved piece.
     * @param start_col The position's column where is the moved piece.
     * @param end_row The position's row where the piece is moved to.
     * @param end_col The position's column where the piece is moved to.
     * @param debug_mode If the debug mode is activated.
     */
    void move_piece(int start_row, int start_col, int end_row, int end_col, bool debug_mode);

    /**
     * @brief Check if a move is valid.
     * @details Check if the start position is not empty and
     * of the player's color, if the end position is not occupied by a piece of
     * the same color, if both start and end positions exists, if path is free and
     * if the move has not been repeted three times in a row.
     * @param start_row The position's row where is the moved piece.
     * @param start_col The position's column where is the moved piece.
     * @param end_row The position's row where the piece is moved to.
     * @param end_col The position's column where the piece is moved to.
     * @para color The color of the player moving their piece.
     * @return True if the move is valid, false otherwise.
     */
    bool is_move_valid(int start_row, int start_col, int end_row, int end_col, Color color);

    /**
     * @brief Check if a player can move at least one of their pieces.
     * @param color The color of the player whose moves are checked.
     * @return True if the player can move, false otherwise.
     */
    bool can_move(Color color);

    /**
     * @brief Check if a player's flag has been found.
     * @param color The color of the player whose flag is checked.
     * @return True if the flag is dead, i.e. has been found, false otherwise.
     */
    bool flag_lost(Color color);


    /**
     * @brief Place a piece with given symbol on the board of the player which color
     * is given on position whose coordonates are given.
     * @details Used during PLACEMENT state. If the position is already occupied,
     * the precedent piece will be removed. Comportement is undefined if the
     * position is not valid or if all pieces of this type has alredy been placed.
     * @param row The row where the piece must be placed.
     * @param col The column where the piece must be placed.
     * @param symbol The symbol of the piece to place.
     */
    void place_pieces(int row, int col, Rank rank, Color color);

    /**
     * @brief Get the board.
     * @return The table of all positions.
     */
    array<array<Case,WIDTH>,HEIGHT>& get_board();

    /**
     * @brief Get the removed pieces of both players.
     * @return The number of removed pieces for each rank and color.
     */
    array<array<int,RANK_NUMBER>,COLOR_NUMBER>& get_removed_pieces();

    /**
     * @brief Flip the visibility of both defender and attacker before battle.
     * @param start The position of the attacker.
     * @param end The position of the defender.
     * @return True whether a battle will take place, false otherwise.
     */
    bool evaluate_battle (Case& start, Case& end);

    bool isEmpty(int startRow, int startCol);
};

#endif // GAMEBOARD_H
