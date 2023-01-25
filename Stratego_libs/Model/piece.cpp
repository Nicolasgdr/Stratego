#include "piece.h"
#include "scout.h"

Piece::Piece(Color color, Rank rank, bool mobility) :
    color(color), rank(rank), visibility(false), mobility(mobility){}

Piece::Piece() :
    color(NONE), rank(EMPTY), visibility(false), mobility(false){}

Piece::Piece(const Piece& other) :
    color(other.color), rank(other.rank), visibility(other.visibility), mobility(other.mobility){}

Color Piece::get_color() const{
    return this->color;
}

Rank Piece::get_rank() const{
    return this->rank;
}

bool Piece::get_visibility() const{
    return this->visibility;
}

void Piece::flip_piece(bool debug_mode){
    this->visibility= !this->visibility || debug_mode;
}

std::vector<const Piece*> Piece::attack(const Piece& other) const {
    std::vector<const Piece*> defeated_pieces;
    if (rank<=other.rank){
        defeated_pieces.push_back(this);
    }
    if (rank>=other.rank){
        defeated_pieces.push_back(&other);
    }
    return defeated_pieces;
}

bool Piece::can_move() const{
    return this->mobility;
}

bool Piece::is_move_valid(int start_row, int start_col, int end_row, int end_col) const{
    return can_move() &&
            ( (start_col==end_col && (start_row==end_row+1 || start_row==end_row-1))
              ||(start_row==end_row && (start_col==end_col+1 || start_col==end_col-1)));
}

bool operator < (const Piece& lhs, const Piece& rhs){
    return lhs.get_rank() < rhs.get_rank();
}

bool operator == (Piece lhs, const Piece& rhs){
    return lhs.get_rank() == rhs.get_rank()
            && lhs.get_color() == rhs.get_color();
}

bool operator != (Piece lhs, const Piece& rhs){
    return lhs.get_rank() != rhs.get_rank()
            || lhs.get_color() != rhs.get_color();
}

std::ostream& operator << ( std::ostream& os, Piece const& piece ) {
    os <<  piece.get_rank() << piece.get_color();
    return os;
}

void Piece::operator = (Piece rhs){
    this->color = rhs.color;
    this->rank = rhs.rank;
    this->visibility = rhs.visibility;
    this->mobility = rhs.mobility;
}

