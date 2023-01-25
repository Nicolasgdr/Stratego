#ifndef PAUSEREPOSITORY_H
#define PAUSEREPOSITORY_H

#include <QString>
#include "../dto/pauseDto.h"
#include "../dao/pauseDao.h"

/**
 * @brief Represents facade class that can access to the PAUSE table.
 */
class PauseRepository{
    /**
     * @brief The pause data access object.
     */
    PauseDao pDao;

public:
    /**
     * @brief Adds a line to the PAUSE table.
     * @param item the field that contains the attributes to add
     */
    void add(PauseDto item);
    /**
     * @brief Deletes a line from the PAUSE table.
     * @param name the attribute name
     * @param gameId the attribute gameId
     */
    void deleteStmt(QString name, int gameId);
    /**
     * @brief Selects the corresponding pause.
     * @param key the primary key of the line to select
     * @return a pausedto containing correct data if the key exists in the table, otherwise
     * an incorrect pseudodto with key field set to -1.
     */
    PauseDto select(int key);
    /**
     * @brief Selects the corresponding pause.
     * @param name the attribute representing the name
     * @param gameId the attribute representing the game Id
     * @return a pausedto containing correct data if the key exists in the table, otherwise
     * an incorrect pseudodto with key field set to -1.
     */
    PauseDto select(QString name, int gameId);
};

#endif // PAUSEREPOSITORY_H
