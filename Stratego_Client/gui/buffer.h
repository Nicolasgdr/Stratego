#ifndef BUFFER_H
#define BUFFER_H

#include <QString>
#include <array>
#include "../Stratego_libs/Model/rank.h"
#include "../Stratego_libs/Model/color.h"

using namespace std;

/**
 * @brief The Buffer class is used to contain temporary informations such
 * as positions or ranks.
 */
class Buffer
{
    Rank rank;
    array<int,2> pos;

public:
    /**
     * @brief Creates a new buffer.
     */
    Buffer();

    /**
     * @brief Sets a rank in the buffer.
     * @param rank The rank to save.
     */
    void set_rank(Rank rank);

    /**
     * @brief Sets a position in the buffer.
     * @param row The row of the position to save.
     * @param col The column of the position to save.
     */
    void set_pos(int row, int col);

    /**
     * @brief Gets to rank currently saved in the buffer.
     * @return The rank currently saved in the buffer.
     */
    Rank get_rank();

    /**
     * @brief Checks if there's currently a rank in the buffer.
     * @return True if a rank is saved, else false.
     */
    bool has_rank();

    /**
     * @brief Checks if a position is currently saved in the buffer.
     * @return True if a position is saved, else false.
     */
    bool has_pos();

    /**
     * @brief Delete rank informations currently in the buffer
     * @return The rank currently in the buffer.
     */
    Rank empty_rank();

    /**
     * @brief Delete the position currently in the buffer.
     * @return The position currently in the buffer.
     */
    array<int,2> empty_pos();
};

#endif // BUFFER_H
