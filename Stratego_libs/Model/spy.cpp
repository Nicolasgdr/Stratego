#include "spy.h"

using namespace std;

Spy::Spy(Color color) : Piece(color, SPY){}

vector<const Piece*> Spy::attack(const Piece& other) const
{
    vector<const Piece*> defeated_pieces;
    if(other.get_rank() == MARSHAL)
        defeated_pieces.push_back(&other);
    else
        defeated_pieces=Piece::attack(other);

    return defeated_pieces;
}
