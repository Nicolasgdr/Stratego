#ifndef GAME_H
#define GAME_H

#include <string>
#include <exception>
#include <fstream>
#include <regex>
#include <algorithm>
#include "Player.hpp"
#include "gameboard.h"
#include "gameState.h"
#include "observ.h"
#include "state_error.h"
#include "bot.h"


using namespace std;

/**
 * @brief The facade of the game
 * @details Contains and update the state of the game, the current player and the board.
 */
class Game : public Observable
{
    struct To_move
    {
        int startRow = 0;
        int startCol = 0;
        int endRow = 0;
        int endCol = 0;

        void clear(){
            *this = {0,0,0,0};
        }

        bool is_empty(){
            return startCol==0 && startRow==0 && endCol ==0 && endRow==0;
        }
    };

    To_move buffer;
    Color current_player;
    GameState state;
    Gameboard board;
    bool debug_mode;
    array<Player,2> players;
    int game_id;
    bool private_game;
    /**
     * @brief bot IA against which we can play.
     */
    Bot bot;
    bool againstBot;

    /**
     * @brief Check if the given file representing the desired positions of the
     * pieces is valid.
     * @details The file must contains four lines of ten space-separated symbols each, where the
     * symbols are: "D", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" and "B"
     * which of these presents in valid quantities, meaning in order:
     * 1, 1, 8, 5, 4, 4, 4, 3, 2, 1, 1, 6.
     * @param file_path The path to the file to verify.
     * @return True if the file is valid, false otherwise.
     */
    bool is_file_correct(string file_path, Color player_color);

    /**
     * @brief Check if the game is over.
     * @details Check if the current player can move and if their flag remain
     * unfound.
     * @return True if the game is over, false otherwise.
     */
    bool is_over();

    /**
     * @brief Set the state of the game.
     * @details Set NOT_STARTED to PLACEMENT.
     * If current_player is BLUE and all pieces have been
     * placed, set PLACEMENT to NEXT_PLAYER.
     * Set PLAYER_TURN to NEXT_PLAYER.
     * If game is not over, set NEXT_PLAYER to PLAYER_TURN,
     * otherwise set NEXT_PLAYER to END_GAME.
     */
    void next_state();

    /**
     * @brief Check if all the pieces of the current player have been placed.
     * @return True if all pieces have been placed, false otherwise.
     */
    bool are_all_pieces_placed(Color player_color);

    /**
     * @brief Convert the given state into a string.
     * @throws invalid_argument if the state is unknow.
     * @param state The state of the game.
     * @return A string representing the state.
     */
    string to_string(GameState state);


public :

    /**
     * @brief Set current_player to the next player.
     * @details Used during PLACEMENT or NEXT_PLAYER state.
     * If the state is PLACEMENT, the current player remains the same until all
     * theirs pieces are placed. If its done set state at NEXT_PLAYER.
     * If the state is NEXT_PLAYER, set RED to BLUE and vice versa. Once its done,
     * if the game is over, set state at END_GAME, otherwise set it at PLAYER_TURN.
     * @throws state_error if the state is not PLAYER_TURN nor NEXT_PLAYER.
     * @throws logic_error if the placement of the current player is not achieved.
     */
    void next_player();

    /**
     * @brief The constructor of Game.
     * @details Initialise the state at NOT_STARTED, the gameboard to
     * a new Gameboard, the debug_mode at false and the current player at NONE.
     */
    Game();

    /**
     * @brief Game
     * @param game_ID
     * @param is_private
     */
    Game(int game_ID, bool is_private, bool againsBot);

    /**
     * @brief Return the current state of the game.
     * @return The state of the game.
     */
    GameState get_state();

    /**
     * @brief Convert symbol as string to rank.
     * @param symbol The string symbolising a piece's rank.
     * @return The associated rank or UNKNOW.
     */
    Rank symbol_to_rank(string symbol);

    /**
     * @brief Set the mode of the game.
     * @details Used during NOT_STARTED state.
     * In debug_mode, pieces will stay visible after a battle.
     * @throws state_error if the state isn't NOT_STARTED.
     * @param debug_mode The mode of the game.
     */
    void set_mode(bool debug_mode);

    /**
     * @brief Start the game by initiating the PLACEMENT state and initialising
     * the current_player at RED.
     * @throws state_error if the state isn't NOT_STARTED.
     * @details Used during NOT_STARTED state.
     */
    void start();

    /**
     * @brief Return the number of pieces of the given rank left to place
     * for the current player.
     * @details Used during the state PLACEMENT.
     * @throws state_error if the state is not PLACEMENT
     * @throws invalid_argument if the rank is UNKNOW.
     * @param rank The piece's rank.
     * @return The number of pieces of this rank left to place.
     */
    int get_pieces_to_place_left (Rank rank, Color player_color);

    /**
     * @brief Place a piece with given rank on the board of the current player
     * on position whose coordinates are given.
     * @details Used during PLACEMENT state.
     * If the position is already occupied, the precedent piece will be removed.
     * The blue pieces must be placed on the top of the board, and the red ones
     * on the bottom.
     * If all the pieces of both players have been placed, set state at PLAYER_TURN,
     * otherwise state remains PLACEMENT.
     * @throws state_error if the state is not PLACEMENT.
     * @throws invalid_argument if the rank is UNKNOW or if all pieces of this rank
     * have already been placed.
     * @throws out_of_range if the given coordinates are outside of the current_player's
     * placement zone.
     * @param row The row where the piece must be placed.
     * @param col The column where the piece must be placed.
     * @param Rank The rank of the piece to place.
     */
    void manual_placement(int row, int col, Rank rank, Color player_color);

    /**
     * @brief Place all pieces of a player following the given model.
     * @details Used during PLACEMENT state.
     * The file contains four lines, each of them containing ten symbols of pieces
     * separated by space. The file will be read from left to right and from top to
     * bottom and the pieces will be placed from left to right and from margin to
     * center. The blue pieces will be place from top to bottom in the board, and
     * the red ones from bottom to top.
     * If the pieces of both players have been placed, set state at PLAYER_TURN,
     * otherwise state remains PLACEMENT.
     * @throws state_error if the state is not PLACEMENT.
     * @throws invalid_argument if the file cannot be opened.
     * @throws domain_error if the given file does not represent a valid placement model.
     * @param file_path The path of the file representing the desired placement for
     * the pieces.
     */
    void file_placement(string file_path, Color player_color);

    /**
     * @brief Return the current player.
     * @details Used during PLACEMENT or PLAYER_TURN state.
     * @throws state_error if the state is neither PLACEMENT nor PLAYER_TURN.
     * @return The color of the current player.
     */
    Color get_current_player();

    /**
     * @brief Get the board with the pieces visible for the current player.
     * @details Used during PLACEMENT, PLAYER_TURN or NEXT_PLAYER state.
     * @throws state_error if the state is neither PLACEMENT, PLAYER_TURN nor NEXT_PLAYER state.
     * @return The board of the current player.
     */
    array<array<pair<Rank, Color>,10>,10> get_board(Color player_color);

    /**
     * @brief Move the piece from start to end.
     * @details Used during PLAYER_TURN state.
     * If the move has been made, set state at NEXT_PLAYER.
     * @throws state_error if the state is not PLAYER_TURN.
     * @throws invalid_argument if the move is not valid.
     * @param startRow The row of the start position.
     * @param startCol The column of the start position.
     * @param endRow The row of the end position.
     * @param endCol The column of the end position.
     */
    void move_piece(int startRow, int startCol, int endRow, int endCol, Color player_color);

    /**
     * @brief Get the dead pieces of both players.
     * @details Used during PLAYER_TURN or NEXT_PLAYER state.
     * @throws state_error if the state is neither PLAYER_TURN nor NEXT_PLAYER.
     * @return The number of dead pieces for each rank and color.
     */
    array<array<int,RANK_NUMBER>, COLOR_NUMBER> get_removed_pieces();

    /**
     * @brief Return the winner of the game.
     * @details Used during END_GAME state.
     * @throws state_error if the state is not END_GAME.
     * @return The color of the winner.
     */
    Color get_winner();

    /**
     * @brief Flip the visibility of both defender and attacker before battle.
     * @param startRow The row of the starting position of the attacker
     * @param startCol The column of the starting position of the attacker
     * @param endRow The row of the position of the defender
     * @param endCol The column of the position of the defender
     */
    bool evaluate_battle(int startRow, int startCol, int endRow, int endCol);

    /**
     * @brief Add a player to the players currently playing the game.
     * @param player The player to add
     */
    void addPlayer(Player player);

    /**
     * @brief Gives the players currently playing the game.
     * @return the players currently playing the game.
     */
    array<Player,2> get_players() const;

    /**
     * @brief Gives the id number of the game.
     * @return the id number of the game.
     */
    int get_game_id() const;

    /**
     * @brief Tells if the game is private or not.
     * @return True if the game is private, else false.
     */
    bool is_private() const;
    /**
     * @brief Indicates if the game has instaciated a bot.
     * @return true if there is a bot, false otherwise
     */
    bool is_against_bot() const;

    /**
    * @brief genMove generates a move when the bot is the current player
    */
    std::array<std::array<int,2>,2> genMove();

    void add_observer(Observer& observer) override;

    void remove_observer(Observer& observer) override;

    void notify_observers() override;


    void setBotBoard();
};

#endif // GAME_H
