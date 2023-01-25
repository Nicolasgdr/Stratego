#include "bot.h"
#include "color.h"
#include <cstdlib>
#include <ctime>

/*std::array<int,2> listen_position(std::string input)
{
    std::array<int,2> pos;

    //Convert to a pair of int
    if(input.size()==2 && input[0]<'k')
        pos = std::array<int,2> {input[1]-'1', input[0]-'a'};
    else if(input.size()==3 && input[1]=='1' && input[2]=='0')
        pos =  std::array<int,2> {9, input[0]-'a'};
    else pos = std::array<int,2> {-1,-1};

    return pos;
}

/*Bot::Bot(Gameboard* board)
{

}

//METHODE GENMOVE POUR TESTER LA BOMBE
std::array<std::array<int,2>,2> Bot::moveMinor()
{

    std::cout << "bot genMove()" << std::endl;
    srand (time (0));

    int startRow;
    int startCol;
    int endCol ;
    int endRow;

    if(currentMinorPos.getColumn()==-1)
        getMinor();

    if(caseBomb.getRow()!=-1){
        std::array<int,2> nextPos = moveMinorToBomb();
        startRow=currentMinorPos.getRow();
        startCol=currentMinorPos.getColumn();
        endRow=nextPos[0];
        endCol=nextPos[1];
        currentMinorPos= board->get_board()[nextPos[0]][nextPos[1]];
        //tmpCurrentMinor= Case(nextPos[0],nextPos[1]);
    }

    else{
        //do {
            startCol = 4;
            startRow= line;
            endCol = startCol;
            endRow= (startRow+1)%9;
        //} while (!board->is_move_valid(startRow,startCol,endRow,endCol,Color::BLUE));
    }




    std::array<int,2> posStart= std::array<int,2> {startRow, startCol};
    std::array<int,2> posEnd = std::array<int,2> {endRow, endCol};
    std::array<std::array<int,2>,2> move = {posStart,posEnd};
    //currentMinorPos= Case(endRow,endCol);
    cout << "startPos: ["<< posStart[0]<<"," <<posStart[1]<< "]  , endPos: [" << posEnd[0] << ","<< posEnd[1] << "]"<< endl;
    line++;
    //currentMinorPos=tmpCurrentMinor;
    cout << "Il y a un mineur en colonne "<<currentMinorPos.getColumn()<< " ,ligne " << currentMinorPos.getRow()<< endl;
    return move;
}*/


int Bot::randomIndex(int max_val){
    std::srand(std::time(nullptr));
    int random_number = std::rand() % max_val;
    return random_number;
}

Case Bot::genHookMove(Case c){
    int row = c.getRow();
    int col = c.getColumn();
    if(row == 0 && col == 0){
        if(board->get_board()[row+1][col].is_empty() || board->get_board()[row+1][col].get_piece_color() != BLUE){
            return Case(row+1,col);
        }
        if(board->get_board()[row][col+1].is_empty() || board->get_board()[row][col+1].get_piece_color() != BLUE){
            return Case(row,col+1);
        }
    }
    if(row == 0 && col == 9){
        if(board->get_board()[row+1][col].is_empty() || board->get_board()[row+1][col].get_piece_color() != BLUE){
            return Case(row+1,col);
        }
        if(board->get_board()[row][col-1].is_empty() || board->get_board()[row][col-1].get_piece_color() != BLUE){
            return Case(row,col-1);
        }
    }
    if(row == 9 && col == 0){
        if(board->get_board()[row-1][col].is_empty() || board->get_board()[row-1][col].get_piece_color() != BLUE){
            return Case(row-1,col);
        }
        if(board->get_board()[row][col+1].is_empty() || board->get_board()[row][col+1].get_piece_color() != BLUE){
            return Case(row,col+1);
        }
    }
    if(row == 9 && col == 9){
        if(board->get_board()[row-1][col].is_empty() || board->get_board()[row-1][col].get_piece_color() != BLUE){
            return Case(row-1,col);
        }
    }
    return Case(row,col-1);
}

Case Bot::genSideMove(Case c){
    int row = c.getRow();
    int col = c.getColumn();
    if(row == 0){
        if(board->get_board()[row+1][col].is_empty() || board->get_board()[row+1][col].get_piece_color() != BLUE){
            return Case(row+1,col);
        }
        if(board->get_board()[row][col+1].is_empty() || board->get_board()[row][col+1].get_piece_color() != BLUE){
            return Case(row,col+1);
        }
        if(board->get_board()[row][col-1].is_empty() || board->get_board()[row][col-1].get_piece_color() != BLUE){
            return Case(row,col-1);
        }
    }
    if(row == 9){
        if(board->get_board()[row-1][col].is_empty() || board->get_board()[row-1][col].get_piece_color() != BLUE){
            return Case(row-1,col);
        }
        if(board->get_board()[row][col+1].is_empty() || board->get_board()[row][col+1].get_piece_color() != BLUE){
            return Case(row,col+1);
        }
        if(board->get_board()[row][col-1].is_empty() || board->get_board()[row][col-1].get_piece_color() != BLUE){
            return Case(row,col-1);
        }
    }
    if(col == 0){
        if(board->get_board()[row+1][col].is_empty() || board->get_board()[row+1][col].get_piece_color() != BLUE){
            return Case(row+1,col);
        }
        if(board->get_board()[row][col+1].is_empty() || board->get_board()[row][col+1].get_piece_color() != BLUE){
            return Case(row,col+1);
        }
        if(board->get_board()[row-1][col].is_empty() || board->get_board()[row-1][col].get_piece_color() != BLUE){
            return Case(row-1,col);
        }
    }
    if(col == 9){
        if(board->get_board()[row+1][col].is_empty() || board->get_board()[row+1][col].get_piece_color() != BLUE){
            return Case(row+1,col);
        }
        if(board->get_board()[row][col-1].is_empty() || board->get_board()[row][col-1].get_piece_color() != BLUE){
            return Case(row,col-1);
        }
    }
    return Case(row-1,col);
}

Case Bot::genCenterMove(Case c){
    int row = c.getRow();
    int col = c.getColumn();
    if(board->contain(Case(row+1,col)) &&
            (board->get_board()[row+1][col].is_empty() || board->get_board()[row+1][col].get_piece_color() != BLUE)){
        return Case(row+1,col);
    }
    if(board->contain(Case(row,col+1)) &&
            (board->get_board()[row][col+1].is_empty() || board->get_board()[row][col+1].get_piece_color() != BLUE)){
        return Case(row,col+1);
    }
    if(board->contain(Case(row,col-1)) &&
            (board->get_board()[row][col-1].is_empty() || board->get_board()[row][col-1].get_piece_color() != BLUE)){
        return Case(row,col-1);
    }
    return Case(row-1,col);
}

Case Bot::genPieceMove(Case c){
    int row = c.getRow();
    int col = c.getColumn();
    if((row == 0 && col == 0) || (row == 0 && col == 9) || (row == 9 && col == 0) || (row == 0 && col == 9)){
        return genHookMove(c);
    }
    if(row == 0 || row == 9 || col == 0 || col == 9){
        return genSideMove(c);
    }
    return genCenterMove(c);
}

Case Bot::selectPieceToMove(){
    std::vector<Case> vec;
    for(int i = 0 ; i < 10 ; i++){
        for(int j = 0 ; j < 10 ; j++){
            if(can_move[i][j])
                vec.push_back(Case(i,j));
        }
    }
    int idx = randomIndex(vec.size());
    return vec.at(idx);
}

std::array<std::array<int,2>,2> Bot::genMove(){
    std::array<std::array<int,2>,2>temp;
    /*if(currentMinorPos.getColumn()!=-1 && caseBomb.getColumn()!=-1 && moveToMake==1){
        moveMinor();*/

    //if(moveToMake==0 && caseBomb.getColumn()!=-1){
        //moveToMake=1;
        //return moveMinor();
        //temp= moveMinor();
        //if(caseBomb.getRow()==currentMinorPos.getRow()&& caseBomb.getColumn()==currentMinorPos.getColumn())
            //caseBomb = {-1,-1};
    //}

    /*else{
        moveToMake=0; //deplacer quelque chose autre que le mineur
        return movePiece();
    }*/

    updateCanMove();
    Case start = selectPieceToMove();
    //start pos
    temp[0][0] = start.getRow();
    temp[0][1] = start.getColumn();
    //end pos
    Case end = genPieceMove(start);
    temp[1][0] = end.getRow();
    temp[1][1] = end.getColumn();
    return temp;
}


/*void Bot::bombSearch(Case start ,Case end){
    cout <<"bomb search"<<endl;
    if(start.get_piece_color()==Color::BLUE && end.get_piece_color()==Color::RED){
        if(start.get_piece().get_rank()!=MINER &&  end.get_piece().get_rank()==BOMB){
            caseBomb=end;
            cout<<"Bomb search" << " caseBomb: [" << caseBomb.getRow()<< ","<< caseBomb.getColumn() << "]"<< endl;

        }
    }
}*/

Bot::Bot(Gameboard *board)
{
    this->board=board;
    //this->caseBomb=Case(-1,-1);
    //this->currentMinorPos= Case(-1,-1);
}



/**
 * @brief Bot::findFree allows to find free cases around the given position
 * @param startRow
 * @param startCol
 * @return
 */
/*std::array<int,2> Bot::findFree(int startRow, int startCol)
{
    Case caseAround ;
    Case caseFree;

    if(startRow!=9) {
        caseAround = board->get_board().at(startRow+1).at(startCol);
        if(caseAround.is_empty())
            return std::array<int,2> {startRow+1,startCol};
    }

    if(startRow!=0){
        caseAround = board->get_board().at(startRow-1).at(startCol);
        if(caseAround.is_empty())
            return std::array<int,2> {startRow-1,startCol};
    }

    if(startCol!=0){
        caseAround = board->get_board().at(startRow).at(startCol-1);
        if(caseAround.is_empty())
            return std::array<int,2> {startRow,startCol-1};
    }

    if(startRow!=9){
        caseAround = board->get_board().at(startRow).at(startCol+1);
        if(caseAround.is_empty())
            return std::array<int,2> {startRow,startCol+1};
    }

    //A IMPLEMENTER : si dans les 4 directions il ne trouve pas d ennemis , doit aller dans une direction ou il n y a pas de pion
    //==>changer le return en bas
    //return std::array<int,2> {startRow+1,startCol};
    return std::array<int,2> {-1,-1}; //si aucune position de libre autour

}

std::array<int,2> Bot::findTarget(int startRow, int startCol)
{
    Case caseAround ;
    Case caseFree;

    if(startRow!=9) {
        caseAround = board->get_board().at(startRow+1).at(startCol);
        if(isRed(caseAround))
            return std::array<int,2> {startRow+1,startCol};
    }

    if(startRow!=0){
        caseAround = board->get_board().at(startRow-1).at(startCol);
        if(isRed(caseAround))
            return std::array<int,2> {startRow-1,startCol};
    }

    if(startCol!=0){
        caseAround = board->get_board().at(startRow).at(startCol-1);
        if(isRed(caseAround))
            return std::array<int,2> {startRow,startCol-1};
    }

    if(startRow!=9){
        caseAround = board->get_board().at(startRow).at(startCol+1);
        if(isRed(caseAround))
            return std::array<int,2> {startRow,startCol+1};
    }

    //A IMPLEMENTER : si dans les 4 directions il ne trouve pas d ennemis , doit aller dans une direction ou il n y a pas de pion
    //==>changer le return en bas
    //return std::array<int,2> {startRow+1,startCol};
    return std::array<int,2> {-1,-1};

}

bool Bot::isRed(Case caseAround ){
    return caseAround.get_piece_color()==Color::RED;
}

void Bot::getMinor()
{
    auto &boardd = board->get_board();
    Piece currentPiece;
    for (unsigned i=0;i<board->get_board().size()-1 ; i++) {
        for (unsigned j=0; j<board->get_board().at(0).size()-1 ;j++ ) {
            currentPiece =board->get_board()[i][j].get_piece();
            if( currentPiece.get_color()==BLUE && currentPiece.get_rank()==3 ){ //means that we are a minor of the bot
                auto findTGT = findFree(i,j);
                if( findTGT[0]!=-1 ){
                    currentMinorPos=boardd[i][j];
                    //currentMinorPos=board->get_board()[i][j];
                    return;
                }
            }
        }
    }
}

std::array<int,2> Bot::moveMinorToBomb()
{
    int startRow;
    int startCol;

    do {
        startRow=currentMinorPos.getRow();
        startCol=currentMinorPos.getColumn();

        if(currentMinorPos.getRow()<caseBomb.getRow()
                && canMoveTo(startRow,startCol,startRow+1,startCol)){
            startRow++;
        }else if(currentMinorPos.getRow()>caseBomb.getRow()
                 && canMoveTo(startRow,startCol,startRow-1,startCol)){
            startRow--;
        }

        else if(currentMinorPos.getColumn()<caseBomb.getColumn()
                && canMoveTo(startRow,startCol,startRow,startCol+1)){
            startCol++;

        }else if(currentMinorPos.getColumn()>caseBomb.getColumn()
                 && canMoveTo(startRow,startCol,startRow,startCol-1)){
            startCol--;

        }
        cout << "currentMinorPos: "<<currentMinorPos.getRow() <<","<< currentMinorPos.getColumn() << endl;

        if(startRow==currentMinorPos.getRow() && startCol==currentMinorPos.getColumn()){
            return std::array<int,2> {caseBomb.getRow(),caseBomb.getColumn()};}

    } while (!canMoveTo(currentMinorPos.getRow(), currentMinorPos.getColumn(), startRow,startCol));

    //    if(startRow==currentMinorPos.getRow() && startCol==currentMinorPos.getColumn()){
    //        return std::array<int,2> {caseBomb.getRow(),caseBomb.getColumn()};}
    //        return std::array<int,2> {startRow,startCol};}

    return std::array<int,2> {startRow,startCol};


}

bool Bot::canMoveTo(int startRow, int startCol, int endRow, int endCol)
{
    if(startRow>9|| startRow<0 || startCol>9 || startCol<0
            || endRow>9|| endRow<0 || endCol>9 || endCol<0 )
        return false;
    if( ((endRow==4)&&(endCol==2 || endCol==3 || endCol==6|| endCol==7)) //check le lac
            ||((endRow==5)&&(endCol==2 || endCol==3 || endCol==6|| endCol==7)) )
        return false;
    if(board->isEmpty(endRow,endCol) )
        return true;
    return false;
}

std::array<std::array<int, 2>, 2> Bot::movePiece()
{
    std::cout << "bot movePiece()" << std::endl;
    std::array<int,2> posEnd;
    srand (time (0));
    int startRow;
    int startCol;
    int endCol ;
    int endRow;
    do {
        startCol = rand()%9+0;
        startRow= rand()%9+0;
        endCol = startCol;
        endRow= startRow+1;
    } while (!board->is_move_valid(startRow,startCol,endRow,endCol,Color::BLUE));
    std::array<int,2> posStart= std::array<int,2> {startRow, startCol};
    if( (posEnd=findTarget(startRow,startCol))[0]==-1 )
        posEnd=findFree(startRow,startCol);

    std::array<std::array<int,2>,2> move = {posStart,posEnd};
    cout << "startPos: ["<< posStart[0]<<"," <<posStart[1]<< "]  , endPos: [" << posEnd[0] << ","<< posEnd[1] << "]"<< endl;
    return move;
}*/


void Bot::setBoard(Gameboard* board)
{
    this->board= board;
    updateCanMove();
}

void Bot::updateCanMove(){
    for(int i = 0 ; i < 10 ; i++){
        for(int j = 0 ; j < 10 ; j++){
            can_move[i][j] = false;
            Case c = board->get_board()[i][j];
            if(!c.is_empty() && c.get_piece_color() == BLUE){
                if(canMove(c)) can_move[i][j] = true;
            }
        }
    }
}

bool Bot::canMove(Case c){
    if(!c.get_piece().can_move())
        return false;
    int row = c.getRow();
    int col = c.getColumn();
    if(row == 0 && col == 0)
        return canMoveUpperLeft(c);
    if(row == 0 && col == 9)
        return canMoveUpperRight(c);
    if(row == 9 && col == 0)
        return canMoveBottomLeft(c);
    if(row == 9 && col == 9)
        return canMoveBottomRight(c);
    if(row == 0) return canMoveTopSide(c);
    if(row == 9) return canMoveBotSide(c);
    if(col == 0) return canMoveLeftSide(c);
    if(col == 9) return canMoveRightSide(c);
    return canMoveOutSides(c);
}

bool Bot::canMoveOutSides(Case c){
    //evite les bords du plateau
    //row != 0 && col != 0 && row != 9 && col != 9
    int row = c.getRow();
    int col = c.getColumn();
    if(board->get_board()[row-1][col].is_empty() && board->contain(Case(row-1,col))) return true;
    else{
        if(board->get_board()[row-1][col].get_piece_color() == RED) return true;
    }
    if(board->get_board()[row+1][col].is_empty() && board->contain(Case(row+1,col))) return true;
    else{
        if(board->get_board()[row+1][col].get_piece_color() == RED) return true;
    }
    if(board->get_board()[row][col-1].is_empty() && board->contain(Case(row,col-1))) return true;
    else{
        if(board->get_board()[row][col-1].get_piece_color() == RED) return true;
    }
    if(board->get_board()[row][col+1].is_empty() && board->contain(Case(row,col+1))) return true;
    else{
        if(board->get_board()[row][col+1].get_piece_color() == RED) return true;
    }
    return false;
}


bool Bot::canMoveUpperLeft(Case c){
    int row = c.getRow();
    int col = c.getColumn();
    if(board->get_board()[row+1][col].is_empty()) return true;
    else{
        if(board->get_board()[row+1][col].get_piece_color() != BLUE) return true;
    }
    if(board->get_board()[row][col+1].is_empty()) return true;
    else{
        if(board->get_board()[row][col+1].get_piece_color() != BLUE) return true;
    }
    return false;
}

bool Bot::canMoveUpperRight(Case c){
    int row = c.getRow();
    int col = c.getColumn();
    if(board->get_board()[row+1][col].is_empty()) return true;
    else{
        if(board->get_board()[row+1][col].get_piece_color() != BLUE) return true;
    }
    if(board->get_board()[row][col-1].is_empty()) return true;
    else{
        if(board->get_board()[row][col-1].get_piece_color() != BLUE) return true;
    }
    return false;
}

bool Bot::canMoveBottomLeft(Case c){
    int row = c.getRow();
    int col = c.getColumn();
    if(board->get_board()[row-1][col].is_empty()) return true;
    else{
        if(board->get_board()[row-1][col].get_piece_color() != BLUE) return true;
    }
    if(board->get_board()[row][col+1].is_empty()) return true;
    else{
        if(board->get_board()[row][col+1].get_piece_color() != BLUE) return true;
    }
    return false;
}

bool Bot::canMoveBottomRight(Case c){
    int row = c.getRow();
    int col = c.getColumn();
    if(board->get_board()[row-1][col].is_empty()) return true;
    else{
        if(board->get_board()[row-1][col].get_piece_color() != BLUE) return true;
    }
    if(board->get_board()[row][col-1].is_empty()) return true;
    else{
        if(board->get_board()[row][col-1].get_piece_color() != BLUE) return true;
    }
    return false;
}

bool Bot::canMoveTopSide(Case c){
    int row = c.getRow();
    int col = c.getColumn();
    if(board->get_board()[row+1][col].is_empty()) return true;
    else{
        if(board->get_board()[row+1][col].get_piece_color() != BLUE) return true;
    }
    if(board->get_board()[row][col+1].is_empty()) return true;
    else{
        if(board->get_board()[row][col+1].get_piece_color() != BLUE) return true;
    }
    if(board->get_board()[row][col-1].is_empty()) return true;
    else{
        if(board->get_board()[row][col-1].get_piece_color() != BLUE) return true;
    }
    return false;
}

bool Bot::canMoveBotSide(Case c){
    int row = c.getRow();
    int col = c.getColumn();
    if(board->get_board()[row-1][col].is_empty()) return true;
    else{
        if(board->get_board()[row-1][col].get_piece_color() != BLUE) return true;
    }
    if(board->get_board()[row][col+1].is_empty()) return true;
    else{
        if(board->get_board()[row][col+1].get_piece_color() != BLUE) return true;
    }
    if(board->get_board()[row][col-1].is_empty()) return true;
    else{
        if(board->get_board()[row][col-1].get_piece_color() != BLUE) return true;
    }
    return false;
}

bool Bot::canMoveLeftSide(Case c){
    int row = c.getRow();
    int col = c.getColumn();
    if(board->get_board()[row+1][col].is_empty()) return true;
    else{
        if(board->get_board()[row+1][col].get_piece_color() != BLUE) return true;
    }
    if(board->get_board()[row][col+1].is_empty()) return true;
    else{
        if(board->get_board()[row][col+1].get_piece_color() != BLUE) return true;
    }
    if(board->get_board()[row-1][col].is_empty()) return true;
    else{
        if(board->get_board()[row-1][col].get_piece_color() != BLUE) return true;
    }
    return false;
}

bool Bot::canMoveRightSide(Case c){
    int row = c.getRow();
    int col = c.getColumn();
    if(board->get_board()[row+1][col].is_empty()) return true;
    else{
        if(board->get_board()[row+1][col].get_piece_color() != BLUE) return true;
    }
    if(board->get_board()[row][col-1].is_empty()) return true;
    else{
        if(board->get_board()[row][col-1].get_piece_color() != BLUE) return true;
    }
    if(board->get_board()[row-1][col].is_empty()) return true;
    else{
        if(board->get_board()[row-1][col].get_piece_color() != BLUE) return true;
    }
    return false;
}
