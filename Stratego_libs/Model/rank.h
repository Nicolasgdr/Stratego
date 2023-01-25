#ifndef RANK_H
#define RANK_H

/**
 * @brief All the possible ranks for the pieces in game.
 */
enum Rank
{
    FLAG,       /**< the flag, power 0, number 1 */
    SPY,        /**< the spy, power 1, number 1 */
    SCOUT,      /**< the scout, power 2, number 8 */
    MINER,      /**< the miner, power 3, number 5 */
    SERGEANT,   /**< the sergeant, power 4, number 4 */
    LIEUTENANT, /**< the lieutenant, power 5, number 4 */
    CAPTAIN,    /**< the captain, power 6, number 4 */
    MAJOR,      /**< the major, power 7, number 3 */
    COLONEL,    /**< the colonel, power 8, number 2 */
    GENERAL,    /**< the general, power 9, number 1 */
    MARSHAL,    /**< the marshal, power 10, number 1 */
    BOMB,       /**< the bomb, power 11, number 6 */

    RANK_NUMBER,/**< the number of ranks in the game */

    UNKNOWN,    /**< unknow rank */
    WATER,      /**< for unaccessible positions */
    EMPTY       /**< default rank */
};

#endif // RANK_H
