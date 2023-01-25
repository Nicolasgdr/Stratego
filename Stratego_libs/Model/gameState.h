#ifndef GAMESTATE_H
#define GAMESTATE_H

/**
 * @brief The differents possible states for the game.
 */

enum GameState
{
    NOT_STARTED, /**< state before the initialisation of the game */
    PLACEMENT,   /**< state of placement of the player's pieces on the board */
    PLAYER_TURN, /**< state of the game during which a player play its turn */
    NEXT_PLAYER, /**< state of the game ending a player's turn */
    END_GAME     /**< state of the game when this one is over */
};

#endif // GAMESTATE_H
