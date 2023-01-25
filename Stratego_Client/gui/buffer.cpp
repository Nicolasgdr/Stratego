#include "buffer.h"

Buffer::Buffer() : rank(EMPTY), pos{-1,-1} {}

void Buffer::set_rank(Rank rank){this->rank=rank;}

void Buffer::set_pos(int row, int col){pos={row,col};}

bool Buffer::has_rank(){return rank!=EMPTY;}

bool Buffer::has_pos(){return pos[0]!=-1;}

Rank Buffer::get_rank(){return rank;}

array<int,2> Buffer::empty_pos()
{
    array<int,2> tmp=pos;
    pos={-1,-1};
    return tmp;
}

