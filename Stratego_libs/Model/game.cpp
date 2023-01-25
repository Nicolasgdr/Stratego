#include "Game.h"
#include <QDebug>

using namespace std;


/* Public, callable at any time */

Game::Game() :
    current_player(NONE), state(NOT_STARTED), board(Gameboard()), debug_mode(false) {}

Game::Game(int game_id, bool is_private, bool is_alone) :
        current_player(NONE), state(NOT_STARTED), board(Gameboard()),
        debug_mode(false), game_id(game_id), private_game(is_private), againstBot(is_alone){
    if(againstBot){
        bot = Bot();
    }
}

GameState Game::get_state()
{
    return state;
}

Rank Game::symbol_to_rank(string symbol)
{
    if(symbol=="F" || symbol=="f" || symbol=="D" || symbol=="d") return FLAG;
    else if(symbol=="1") return SPY;
    else if(symbol=="2") return SCOUT;
    else if(symbol=="3") return MINER;
    else if(symbol=="4") return SERGEANT;
    else if(symbol=="5") return LIEUTENANT;
    else if(symbol=="6") return CAPTAIN;
    else if(symbol=="7") return MAJOR;
    else if(symbol=="8") return COLONEL;
    else if(symbol=="9") return GENERAL;
    else if(symbol=="10") return MARSHAL;
    else if(symbol=="B" || symbol=="b") return BOMB;
    else return UNKNOWN;
}


/* Public, callable if the game is in the right state */

void Game::set_mode(bool debug_mode)
{
    if (state!=NOT_STARTED)
        throw state_error("Method set_mode() must be called during NOT_STARTED state, state is "+to_string(state));

    this->debug_mode=debug_mode;
}

void Game::start()
{
    if (state!=NOT_STARTED)
        throw state_error("Method start() must be called during NOT_STARTED state, state is "+to_string(state));

    current_player=RED;
    state=PLACEMENT;

    notify_observers();
}

int Game::get_pieces_to_place_left(Rank rank, Color player_color)
{
    if (state!=PLACEMENT)
        throw state_error("Method get_pieces_to_place_left() must be called during PLACEMENT state, state is "+to_string(state));
    if (rank>=RANK_NUMBER)
        throw invalid_argument("Unknown rank");

    return board.get_removed_pieces()[player_color][rank];
}

void Game::manual_placement(int row, int col, Rank rank, Color player_color)
{
    if (state!=PLACEMENT)
        throw state_error("Method manual_placement() must be called during PLACEMENT state, state is "+to_string(state));
    if (rank>=RANK_NUMBER)
        throw invalid_argument("Unknown rank");
    if (get_pieces_to_place_left(rank, player_color)<=0)
        throw invalid_argument("All pieces with this rank have already been placed");
    if (!board.contain(Case(row, col)))
        throw out_of_range("This position is not within the board");
    if (player_color==RED && row<6)
        throw out_of_range("RED must place their pieces between row 7 and row 10");
    if (player_color==BLUE && row>3)
        throw out_of_range("BLUE must place their pieces between row 1 and row 4");

    board.place_pieces(row, col, rank, player_color);

    next_state();

    notify_observers();
}

void Game::file_placement(string file_path, Color player_color)
{
    if(state!=PLACEMENT)
        throw state_error("Method file_placement() must be called during PLACEMENT state,"
                          " state is "+to_string(state));
    ifstream ifs;
    ifs.open(file_path);
    if(!ifs.is_open())
        throw invalid_argument("Cannot open the path");
    ifs.close();
    if(!is_file_correct(file_path, player_color))
        throw domain_error("Invalid format for pieces placement");
    ifs.open(file_path, ios::in);

    string symbol;

    for(unsigned file_row=0; file_row<4; file_row++)
    {
        for(unsigned col=0; col<10; col++){
            if(col<9) getline(ifs,symbol,' ');
            else getline(ifs,symbol);

            //if RED, place from row 9 to row 6
            //if BLUE, place from row 0 to row 3
            unsigned board_row = (player_color==RED) ? 9-file_row : file_row;

            board.place_pieces(board_row, col, symbol_to_rank(symbol), player_color);
        }
    }
    qDebug()<<board.get_board()[0][0].get_piece().get_rank();
    ifs.close();

    next_state();

    notify_observers();
}

Color Game::get_current_player()
{
    if (state!=PLACEMENT && state!=PLAYER_TURN && state!=NEXT_PLAYER)
        throw state_error("Method get_current_player() must be called during PLACEMENT or PLAYER_TURN state,"
                          " state is "+to_string(state));

    return current_player;
}

array<array<pair<Rank, Color>,10>,10> Game::get_board(Color player_color)
{
    if(state!=PLACEMENT && state!=PLAYER_TURN && state!=NEXT_PLAYER)
        throw state_error("Method get_board() must be called during PLACEMENT, PLAYER_TURN or NEXT_PLAYER state,"
                          " state is "+to_string(state));

    array<array<pair<Rank, Color>,10>,10> result;
    int row;
    int col;

    for(array<Case,10> line : board.get_board())
    {
        for(Case pos : line)
        {
            row=pos.getRow();
            col=pos.getColumn();

            if (!board.contain(pos)){
                result[row][col].first=WATER;
                result[row][col].second=NONE;
            } else if (!pos.is_empty()){
                const Piece& piece=pos.get_piece();
                if(piece.get_color()==player_color || piece.get_visibility())
                {
                    result[pos.getRow()][pos.getColumn()].first=piece.get_rank();
                } else
                {
                    result[pos.getRow()][pos.getColumn()].first=UNKNOWN;
                }
                result[pos.getRow()][pos.getColumn()].second=piece.get_color();
            } else {
                result[pos.getRow()][pos.getColumn()].first=EMPTY;
                result[pos.getRow()][pos.getColumn()].second=NONE;
            }
        }
    }
    return result;
}

void Game::move_piece(int startRow, int startCol, int endRow, int endCol, Color player_color)
{
    if (state!=PLAYER_TURN)
        throw state_error("Method move_piece() must be called during PLAYER_TURN state,"
                          " state is "+to_string(state));
    if (!board.is_move_valid(startRow, startCol, endRow, endCol, current_player))
        throw invalid_argument("Invalid move");
    if (current_player != player_color)
        throw invalid_argument("Wrong player");

    bool battle = evaluate_battle(startRow,startCol,endRow,endCol);
    if (battle){
        buffer = {startRow, startCol, endRow, endCol};
    }
    if (!battle) {
        board.move_piece(startRow, startCol, endRow, endCol,debug_mode);
        notify_observers();
    }
    next_state();
}

bool Game::evaluate_battle(int startRow, int startCol, int endRow, int endCol){
    if (state!=PLAYER_TURN)
        throw state_error("Method evaluate_battle() must be called during PLAYER_TURN state,"
                          " state is "+to_string(state));
    if (!board.is_move_valid(startRow, startCol, endRow, endCol, current_player))
        throw invalid_argument("Invalid move");

    Case& start = board.get_board()[startRow][startCol];
    Case& end = board.get_board()[endRow][endCol];

    return board.evaluate_battle(start, end);
}

array<array<int,RANK_NUMBER>, COLOR_NUMBER> Game::get_removed_pieces()
{
    if (state!=PLAYER_TURN && state!=NEXT_PLAYER)
        throw state_error("Method get_removed_pieces() must be called during PLAYER_TURN or NEXT_PLAYER state,"
                          " state is "+to_string(state));

    return array<array<int,RANK_NUMBER>,COLOR_NUMBER>(board.get_removed_pieces()); // Copie défensive
}

Color Game::get_winner()
{
    if (state!=END_GAME)
        throw state_error("Method get_winner() must be called during END_GAME state, state is "+to_string(state));

    return (current_player==RED) ? BLUE : RED;

}

void Game::next_player()
{
    if(state!=NEXT_PLAYER)
        throw state_error("Method next_player() must be called during NEXT_PLAYER state, state is "+to_string(state));

    current_player = Color((current_player + 1) %COLOR_NUMBER);

    notify_observers();
    if(!buffer.is_empty()){
        qDebug()<<buffer.startRow<< buffer.startCol<< buffer.endRow << buffer.endCol;
        board.move_piece(buffer.startRow, buffer.startCol, buffer.endRow, buffer.endCol,debug_mode);
        buffer.clear();
    }

    next_state();
}


/* Private */

bool Game::is_file_correct(string file_path, Color player_color)
{
    ifstream file;
    file.open(file_path);
    bool is_correct = file.is_open();

    string symbol;
    unsigned symbol_cpt=0;
    unsigned row_cpt=0;
    unsigned col_cpt;
    int rank_cpt[RANK_NUMBER]{};
    while(is_correct && row_cpt<4 && symbol_cpt<40)
    {
        col_cpt=0;
        while(is_correct && col_cpt<10 && symbol_cpt<40)
        {
            if(col_cpt<9) getline(file,symbol,' ');
            else getline(file,symbol);          // End of line
            Rank rank=symbol_to_rank(symbol);
            is_correct &= rank!=UNKNOWN;
            if(is_correct)
            {
                rank_cpt[rank]++;
                symbol_cpt++;
                is_correct &= rank_cpt[rank]<=get_pieces_to_place_left(rank, player_color);
            }
            col_cpt++;
        }

        row_cpt++;

    }

    is_correct &= symbol_cpt==40 && row_cpt==4 && col_cpt==10;

    file.close();
    return is_correct;
}

bool Game::is_over()
{
    return !board.can_move(current_player)
            || board.flag_lost(current_player);
}

void Game::next_state()
{
    switch (state)
    {
    case(NOT_STARTED) : state=PLACEMENT; break;
    case(PLACEMENT) :
        if(are_all_pieces_placed(RED) && are_all_pieces_placed(BLUE)) {state=PLAYER_TURN; }
        break;
    case(PLAYER_TURN) :
        state=NEXT_PLAYER;
        break;
    case(NEXT_PLAYER) : state= is_over() ? END_GAME : PLAYER_TURN; break;
    case(END_GAME) : ;
    }
}

bool Game::are_all_pieces_placed(Color player_color)
{
    for(int nb : array<int, RANK_NUMBER>(board.get_removed_pieces()[player_color]))
    {
        if(nb!=0) return false;
    }
    return true;
}

string Game::to_string(GameState state)
{
    switch (state)
    {
    case NOT_STARTED : return "NOT_STARTED";
    case PLACEMENT : return "PLACEMENT";
    case PLAYER_TURN : return "PLAYER_TURN";
    case NEXT_PLAYER : return "NEXT_PLAYER";
    case END_GAME : return "END_GAME";
    default : throw invalid_argument("Unknown state");
    }
}


void Game::addPlayer(Player player){
    int position = (int)player.getColor();
    players[position]= player;
}

array<Player,2> Game::get_players() const {
    return players;
}

int Game::get_game_id() const {
    return game_id;
}

bool Game::is_private() const{
    return private_game;
}

bool Game::is_against_bot() const{
    return againstBot;
}

std::array<std::array<int,2>,2> Game::genMove()
{
    if(state != PLAYER_TURN)
        throw state_error("Method genMove() must be called during PLAYER_TURN state, state is "+to_string(state));
    cout << state << endl;
    return bot.genMove();
}

// Observer-Observable pattern

void Game::add_observer(Observer& observer)
{
    observers.push_back(&observer);
}

void Game::remove_observer(Observer& observer)
{
    observers.remove(&observer);
}

void Game::notify_observers()
{
    for(Observer* obs : observers)
    {
        obs->update();
    }
}


void Game::setBotBoard(){
    bot.setBoard(&board);
}
