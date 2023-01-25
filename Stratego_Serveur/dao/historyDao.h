#ifndef HISTORYDAO_H
#define HISTORYDAO_H

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <vector>
#include "dto/historyDto.h"

using namespace std;

/**
 * @brief The history data access object.
 */
class HistoryDao
{

public:
    /**
     * @brief Constructs a history data access object.
     */
    HistoryDao();
    /**
     * @brief Inserts a history line to the table.
     * @param item the item to insert
     */
    void insert(HistoryDto item);
    /**
     * @brief Deletes a tuple from the table.
     * @param key the key of the tuple to delete
     */
    void deleteStmt(int key);
    /**
     * @brief Updates a tuple from the table.
     * @param item the item containing informations about the tuple to update
     */
    void update(HistoryDto item);
    /**
     * @brief Selects all the tuples from the table.
     * @return a vector containg for each tuple a history dto
     */
    vector<HistoryDto> selectAll();
    /**
     * @brief Selects a tuple.
     * @param key the key of the tuple to select
     * @return the corresponding historyDto or an incorrect one with a key set to -1
     */
    HistoryDto select(int key);

    vector<HistoryDto> selectAll(UserDto item1, UserDto item2);
};

#endif // HISTORYDAO_H
