#include "case.h"

Case::Case() : row(-1), col(-1), piece_ptr(nullptr){}

Case::Case(int row, int col) : row(row), col(col), piece_ptr(nullptr){}

int Case::getRow()const{
    return row;
}

int Case::getColumn()const{
    return col;
}

Piece& Case::get_piece() const{
    return *piece_ptr;
}

void Case::set_piece(Piece& piece){
    piece_ptr = &piece;
}

void Case::flip_piece(bool debug_mode){
    piece_ptr->flip_piece(debug_mode);
}

void Case::remove_Piece(){
    piece_ptr=nullptr;
}

Color Case::get_piece_color(){
    if(piece_ptr!=nullptr) return piece_ptr->get_color();
    return NONE;
}


bool Case::is_neighbor(Case other){
    return ( (this->is_same_row(other) && this->col + 1 == other.col)
         || (this->is_same_row(other) && this->col - 1 == other.col)
         || (this->is_same_column(other) && this->row + 1 == other.row)
         || (this->is_same_column(other) && this->row - 1 == other.row));

}

bool Case::is_same_row(Case other){
    return this->row == other.row;
}

bool Case::is_same_column(Case other){
    return this->col == other.col;
}

bool Case::is_empty(){
    return piece_ptr==nullptr;
}

bool operator ==(const Case& lhs, const Case& rhs)
{
    return lhs.getRow()==rhs.getRow() && lhs.getColumn()==rhs.getColumn();
}

bool operator !=(const Case& lhs, const Case& rhs)
{
    return !(lhs==rhs);
}
