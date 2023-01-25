#ifndef USERDAO_H
#define USERDAO_H

#include <QtSql/QSqlQuery>
#include "dto/userDto.h"
#include <vector>
#include <QString>

/**
 * @brief The stat data access object.
 */
class UserDao
{
public:
    /**
     * @brief Constructs a user data access object.
     */
    UserDao();
    /**
     * @brief Inserts a user line to the table.
     * @param item the item to insert
     */
    void insert(UserDto item);
    /**
     * @brief Deletes a tuple from the table.
     * @param key the key of the tuple to delete
     */
    void deleteStmt(int key);
    /**
     * @brief Updates a tuple from the table.
     * @param item the item containing informations about the tuple to update
     */
    void update(UserDto item);
    /**
     * @brief Selects all the tuples from the table.
     * @return a vector containg for each tuple a user dto
     */
    vector<UserDto> selectAll();
    /**
     * @brief Selects a tuple.
     * @param key the key of the tuple to select
     * @return the corresponding userDto or an incorrect one with a key set to -1
     */
    UserDto select(int key);
    /**
     * @brief Selects a tuple.
     * @param name the name of the user
     * @return the corresponding userDto or an incorrect one with a key set to -1
     */
    UserDto select(string name);

    int exist(string name);

};

#endif // USERDAO_H
