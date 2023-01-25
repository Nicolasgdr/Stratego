#include "miner.h"

using namespace std;

Miner::Miner(Color color) : Piece(color, MINER){}

vector<const Piece*> Miner::attack(const Piece& other) const
{
    vector<const Piece*> defeated_pieces;
    if(other.get_rank()==BOMB)
        defeated_pieces.push_back(&other);
    else
        defeated_pieces=Piece::attack(other);

    return defeated_pieces;
}

