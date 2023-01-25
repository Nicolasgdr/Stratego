#ifndef BOT_H
#define BOT_H
#include <iostream>
#include <array>
#include "gameboard.h"
#include <time.h>

class Bot
{
public:
    Bot() = default;
    std::array<std::array<int,2>,2> genMove();
    //ICI BOMB
    //void bombSearch(Case start ,Case end);
    Bot(Gameboard* board);
    /*int line=3;
    bool canMoveTo(int startRow , int startCol, int endRow, int endCol);*/
    void setBoard(Gameboard* board);
    void updateCanMove();

    bool canMove(Case c);
    bool canMoveOutSides(Case c);
    bool canMoveUpperLeft(Case c);
    bool canMoveUpperRight(Case c);
    bool canMoveBottomLeft(Case c);
    bool canMoveBottomRight(Case c);
    bool canMoveTopSide(Case c);
    bool canMoveBotSide(Case c);
    bool canMoveLeftSide(Case c);
    bool canMoveRightSide(Case c);

    int randomIndex(int max);
    Case genPieceMove(Case c);
    Case genHookMove(Case c);
    Case genSideMove(Case c);
    Case genCenterMove(Case c);
    Case selectPieceToMove();
private:
    std::array<std::array<bool,10>,10> can_move;
    Gameboard* board;
    /*Case caseBomb; // 1,1
    std::array<std::array<int,2>,2> moveMinor();
    std::array<std::array<int,2>,2> movePiece();
    std::array<int,2>findTarget(int startRow, int startCol);
    std::array<int,2>findFree(int startRow, int startCol);
    bool isRed(Case caseAround);
    void getMinor();
    std::array<int,2> moveMinorToBomb();
    Case posEnd;
    Case currentMinorPos; //4,1
    Case tmpCurrentMinor;
    int moveToMake=0;*/

};

#endif // BOT_H
