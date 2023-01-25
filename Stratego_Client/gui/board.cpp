#include "board.h"

using namespace cvrt;

Board::Board(QWidget * parent) :
    QWidget(parent), blue_zone(Zone(this, BLUE)), central_zone(Zone(this, NONE)), red_zone(Zone(this, RED))
{
    layout.setSpacing(0);
    layout.addWidget(&blue_zone);
    layout.addWidget(&central_zone);
    layout.addWidget(&red_zone);
    layout.setContentsMargins(0,0,0,0);

    for(int col=0; col<10; col++)
    {
        for(int row=0; row<10; row++)
        {
            if(row<4)
            {
                tiles[row][col]=Tile(&blue_zone);
                ((QGridLayout*) blue_zone.layout())->addWidget(&tiles[row][col], row*TILE_SIZE, col*TILE_SIZE);
            } else if(row<6)
            {
                tiles[row][col]=Tile(&central_zone);
                ((QGridLayout*) central_zone.layout())->addWidget(&tiles[row][col], (row-4)*TILE_SIZE, col*TILE_SIZE);
            } else
            {
                tiles[row][col]=Tile(&red_zone);
                ((QGridLayout*) red_zone.layout())->addWidget(&tiles[row][col], (row-6)*TILE_SIZE, col*TILE_SIZE);
            }

            tiles[row][col].setMaximumSize(TILE_SIZE,TILE_SIZE);
            tiles[row][col].setMinimumSize(TILE_SIZE,TILE_SIZE);
            tiles[row][col].setStyleSheet(" QPushButton { border: none; }");

            QObject::connect(&tiles[row][col], &Tile::clicked, [=, this]{emit this->pos_selected(row,col);});

        }
    }
}

void Board::update(array<array<pair<Rank,Color>,10>,10> new_board)
{
    for(int row=0; row<10; row++)
    {
        for(int col=0; col<10; col++)
        {
            if (to_qstring(new_board[row][col].first) == "N/A"){
                tiles[row][col].setStyleSheet(" QPushButton { border: none; }");
            } else {
                tiles[row][col].setStyleSheet(" QPushButton {"
                                              " border: none;"
                                              " background-image:url('../Stratego_Client/img/"
                                              + to_qstring(new_board[row][col].first)
                                              + to_qstring(new_board[row][col].second)
                                              +".png');"
                                               " background-repeat: no-repeat;"
                                               "}");
            }
        }
    }
}

