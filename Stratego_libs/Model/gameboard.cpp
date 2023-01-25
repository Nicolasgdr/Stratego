#include <iostream>
#include "gameboard.h"
#include "flag.h"
#include "spy.h"
#include "scout.h"
#include "miner.h"
#include "bomb.h"

using namespace std;

Gameboard::Gameboard()
{
    for(int i=0; i<RANK_NUMBER; i++)
    {
        removed_pieces[RED][i]=MULTIPLICITIES[i];
        removed_pieces[BLUE][i]=MULTIPLICITIES[i];
    }
    for(int row=0; row<(int) HEIGHT; row++)
    {
        for(int col=0; col<(int) WIDTH; col++)
        {
            cases[row][col]=Case(row,col);
        }
    }
    for (int nb = 0; nb < 2 ; nb++){
        last_positions[RED].push_front(pair<Case,Piece>());
        last_positions[BLUE].push_front(pair<Case,Piece>());
    }
}

//==========================================================
//      CHECK BOARD
//==========================================================

bool Gameboard::contain(Case pos)
{
    int col = pos.getColumn();
    int row = pos.getRow();
    bool contain = true;

    contain &= col < (int) WIDTH;
    contain &= col >= 0;
    contain &= row < (int) HEIGHT;
    contain &= row >= 0;

    //The two central forbidden zones
    contain &= !((col == 2 || col == 3 || col == 6 || col == 7)
                 && (row == 4 || row == 5));

    return contain;
}

//==========================================================
//          MOVE PIECES
//==========================================================

void Gameboard::move_piece(int start_row, int start_col, int end_row, int end_col, bool debug_mode)
{
    Case& start  = cases[start_row][start_col];
    Case& end    = cases[end_row][end_col];

    add_last_move(start, start.get_piece_color());
    if(!end.is_empty())
        battle(start, end, debug_mode);
    if(!start.is_empty())
        move(start, end);
}

bool Gameboard::evaluate_battle(Case& start, Case& end){


    if (!end.is_empty()){
        Case& attPos = cases[start.getRow()][start.getColumn()];
        Case& defPos = cases[end.getRow()][end.getColumn()];
        flip(attPos,true);
        flip(defPos,true);
        return true;
    }
    return false;
}

bool Gameboard::isEmpty(int startRow, int startCol)
{
    return this->cases[startRow][startCol].is_empty();
}

void Gameboard::battle(Case& start, Case& end, bool debug_mode){
    vector<const Piece*> dead;
    const Piece& attacker = start.get_piece();
    const Piece& defender = end.get_piece();

    Case& attPos = cases[start.getRow()][start.getColumn()];
    Case& defPos = cases[end.getRow()][end.getColumn()];
    flip(attPos,debug_mode);
    flip(defPos,debug_mode);

    dead = attacker.attack(end.get_piece());
    for(const Piece* piece : dead)
    {
        Color color = piece->get_color();
        removed_pieces[color][piece->get_rank()]++;
        if(*piece==attacker) start.remove_Piece();
        if(*piece==defender) end.remove_Piece();
    }
}

void Gameboard::move(Case& start, Case& end){
    end.set_piece(start.get_piece());
    start.remove_Piece();
}

void Gameboard::flip(Case& pos, bool debug_mode){
    pos.flip_piece(debug_mode);
}

//==========================================================
//          CHECK MOVE
//==========================================================

bool Gameboard::is_move_valid(int start_row, int start_col, int end_row, int end_col, Color color)
{
    if(!contain(Case(start_row,start_col)) || !contain(Case(end_row,end_col)))
    {
        return false;
    }

    Case start=cases[start_row][start_col];
    Case end=cases[end_row][end_col];

    if (!start.is_empty()){
    bool valid = start!=end;
    valid &= start.get_piece_color()== color; //Move a piece of their color
    valid &= end.is_empty() || start.get_piece_color() != end.get_piece_color();
    valid &= start.get_piece().is_move_valid(start_row, start_col, end_row, end_col);
    valid &= last_positions[color].front()!=pair<Case,Piece>(end,start.get_piece())
            || last_positions[color].back()!=pair<Case,Piece>(start,start.get_piece());
    valid &= is_path_free(start, end);

    return valid;
    }
    return false;
}

bool Gameboard::is_path_free(Case& start, Case& end)
{
    int startRow    = start.getRow();
    int startCol    = start.getColumn();
    int endRow      = end.getRow();
    int endCol      = end.getColumn();

    if(start.is_neighbor(end)) return true;

    if(startCol >endCol || startRow > endRow)
        return is_path_free(end, start);

    if(start.is_same_column(end))
        for(int row = startRow + 1; row < endRow; row++)
        {
            Case position(row, startCol);
            if(!contain(position)) return false;
            if(!cases[row][startCol].is_empty()) return false;
        }
    else if(start.is_same_row(end))
        for(int col = start.getColumn() + 1; col < end.getColumn(); col++)
        {
            Case position(startRow, col);
            if(!contain(position)) return false;
            if(!cases[startRow][col].is_empty()) return false;
        }
    return true;
}

bool Gameboard::can_move(Color color)
{
    for(array<Case,WIDTH> line : cases)
    {
        for(Case position : line){
            if(!position.is_empty() && position.get_piece_color()==color && position.get_piece().can_move())
            {
                int row=position.getRow();
                int col=position.getColumn();
                if(is_move_valid(row, col, row, col+1,color)
                        || is_move_valid(row, col, row, col-1,color)
                        || is_move_valid(row, col, row+1, col,color)
                        || is_move_valid(row, col, row-1, col,color))
                    return true;
            }
        }
    }
    return false;
}

//==========================================================
//          FLAGS
//==========================================================

bool Gameboard::flag_lost(Color color)
{
    return removed_pieces[color][FLAG] != 0;
}


//==========================================================
//          PLACE PIECES
//==========================================================

void Gameboard::place_pieces(int row, int col, Rank rank, Color color)
{
    if(!cases[row][col].is_empty())
        removed_pieces[color][cases[row][col].get_piece().get_rank()]++;

    switch(rank)
    {
        case(FLAG)  :
            flags[color].push_front(Flag(color));
            cases[row][col].set_piece(flags[color].front());
            break;
        case(SPY)   :
            spies[color].push_front(Spy(color));
            cases[row][col].set_piece(spies[color].front());
            break;
        case(SCOUT) :
            scouts[color].push_front(Scout(color));
            cases[row][col].set_piece(scouts[color].front());
            break;
        case(MINER) :
            miners[color].push_front(Miner(color));
            cases[row][col].set_piece(miners[color].front());
            break;
        case(BOMB)  :
            bombs[color].push_front(Bomb(color));
            cases[row][col].set_piece(bombs[color].front());
            break;
        default     :
            regular_pieces[color][rank].push_front(Piece(color, rank));
            cases[row][col].set_piece(regular_pieces[color][rank].front());
    }

    removed_pieces[color][rank]--;
}


//==========================================================
//          GETTERS
//==========================================================

array<array<Case,Gameboard::WIDTH>,Gameboard::HEIGHT>& Gameboard::get_board()
{
    return cases;
}

array<array<int,RANK_NUMBER>,COLOR_NUMBER>& Gameboard::get_removed_pieces()
{
    return removed_pieces;
}

//==========================================================
//          LAST MOVES
//==========================================================

void Gameboard::add_last_move(const Case& position, Color color)
{
    last_positions[color].pop_back();
    last_positions[color].push_front(pair<Case,Piece&>(position,position.get_piece()));
}

