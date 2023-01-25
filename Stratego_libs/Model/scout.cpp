#include "scout.h"

Scout::Scout(Color color) : Piece(color, SCOUT){}

bool Scout::is_move_valid(int start_row, int start_col, int end_row, int end_col) const
{
    return (start_col==end_col || start_row==end_row);
}
