#ifndef STATREPOSITORY_H
#define STATREPOSITORY_H
#include "dao/statDao.h"

/**
 * @brief Represents facade class that can access to the STAT table.
 */
class statRepository
{
private:
    /**
     * @brief The stat data access object.
     */
    StatDao statDao;

public:
    /**
     * @brief Constructs a statRepository.
     */
    statRepository();
    /**
     * @brief Selects the corresponding stat line.
     * @param stat the StatDto that contains the attributes to select the correct line.
     * @return a statdto containing correct data if the attributes exist in the table, otherwise
     * an incorrect statdto with key field set to -1.
     */
    StatDto select(StatDto stat);
    /**
     * @brief Adds a line to the STAT table.
     * @param stat the field that contains the attributes to add
     */
    void add(StatDto stat);
    /**
     * @brief Removes a line from the STAT table.
     * @param key the primary key that indicates the line to remove
     */
    void remove(int key);
    /**
     * @brief Selects the corresponding stat line.
     * @param name the name corresponding to the name attribute
     * @return a statdto containing correct data if the name exists in the table, otherwise
     * an incorrect statdto with key field set to -1.
     */
    StatDto get(string name);
    /**
     * @brief Updates line(s) in the STAT table.
     * @param stat the field that contains the attributes to update
     */
    void update(StatDto stat);
    /**
     * @brief Gets the number of victory(ies)
     * @param name the attribute name to select the victories
     * @return the number of victories
     */
    int getNbVictory(string name);
};

#endif // STATREPOSITORY_H
