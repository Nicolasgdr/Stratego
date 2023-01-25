#include "deck.h"

using namespace cvrt;

Deck::Deck(QWidget * parent, Color color) :
    QWidget(parent), color(color)
{
    QString basic_url="../Stratego_Client/img/counter_";
    for(int rank=0; rank<RANK_NUMBER; rank++)
    {
        QString rankString = basic_url+to_qstring((Rank) rank)+".jpg";
        QString rankColorString = basic_url+to_qstring((Rank) rank)+to_qstring(color)+".jpg";
        counters[rank]=Counter(this);
        counters[rank].default_style(rankString, rankColorString);

        layout.addWidget(&counters[rank], rank/4*COUNTER_WIDTH, rank%4*COUNTER_HEIGHT);
        layout.setSpacing(0);
        layout.setContentsMargins(0,10,0,10);
        counters[rank].set_fixed_size(COUNTER_WIDTH,COUNTER_HEIGHT);
        QObject::connect(&counters[rank], &Counter::clicked, [this, rank]{emit this->rank_selected(Rank(rank));});
    }
}

void Deck::setGame(game_info game){
    this->game = game;
}

void Deck::update(GameState state, Color player)
{
    array<int,RANK_NUMBER> nbs;
    if(state==PLACEMENT)
    {
        nbs = array<int,RANK_NUMBER>();
        for(int rank=0; rank<RANK_NUMBER; rank++){
            nbs[rank]= game.piecesToPlaceLeft[rank].first;
        }
    }
    else if(state==NEXT_PLAYER)
        nbs = game.removedPieces[color];

    for(int rank=0; rank<RANK_NUMBER; rank++)
    {
        counters[rank].swap_background(color==player);

        counters[rank].setText( QVariant(nbs[rank]).toString() + "    " );
        if (state==PLACEMENT && color!=player)
            counters[rank].setText("");
    }
}
