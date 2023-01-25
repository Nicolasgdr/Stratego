#ifndef PAUSEDAO_H
#define PAUSEDAO_H

#include <QString>
#include "../dto/pauseDto.h"

/**
 * @brief The pause data access object.
 */
class PauseDao
{
public:
    /**
     * @brief Constructs a pause data access object.
     */
    PauseDao();
    /**
     * @brief Inserts a pause line to the table.
     * @param item the item to insert
     */
    void insert(PauseDto item);
    /**
     * @brief Deletes a tuple from the table.
     * @param key the key of the tuple to delete
     */
    void deleteStmt(QString name, int gameId);
    /**
     * @brief Selects a tuple.
     * @param key the key of the tuple to select
     * @return the corresponding pauseDto or an incorrect one with a key set to -1
     */
    PauseDto select(int key);
    /**
     * @brief Selects a tuple.
     * @param name the name of the user
     * @param gameId the game id of the game
     * @return the corresponding pauseDto or an incorrect one with a key set to -1
     */
    PauseDto select(QString name, int gameId);
};

#endif // PAUSEDAO_H
