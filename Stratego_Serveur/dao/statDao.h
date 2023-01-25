#ifndef STATDAO_H
#define STATDAO_H
#include <vector>
#include <QtSql/QSqlQuery>
#include <string>
#include "dto/statDto.h"

using namespace std;

/**
 * @brief The stat data access object.
 */
class StatDao
{
public:
    /**
     * @brief Constructs a stat data access object.
     */
    StatDao();
    /**
     * @brief Inserts a stat line to the table.
     * @param item the item to insert
     */
    void insert(StatDto item);
    /**
     * @brief Deletes a tuple from the table.
     * @param key the key of the tuple to delete
     */
    void deleteStmt(int key);
    /**
     * @brief Gets the number of victories.
     * @param name the nmae of the user to get victories
     * @return the number of victories
     */
    int getNbVictory(string name);
    /**
     * @brief Updates a tuple from the table.
     * @param item the item containing informations about the tuple to update
     */
    void update(StatDto item);
    /**
     * @brief Selects all the tuples from the table.
     * @return a vector containg for each tuple a stat dto
     */
    vector<StatDto> selectAll();
    /**
     * @brief Selects a tuple.
     * @param key the key of the tuple to select
     * @return the corresponding statDto or an incorrect one with a key set to -1
     */
    StatDto select(int key);
    /**
     * @brief Selects a tuple.
     * @param name the name of the user
     * @return the corresponding statDto or an incorrect one with a key set to -1
     */
    StatDto select(string name);
};

#endif // STATDAO_H
