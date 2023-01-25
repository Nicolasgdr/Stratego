#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "dao/userDao.h"
using namespace std;
/**
 * @brief Represents facade class that can access to the USER table.
 */
class userRepository
{
private:
    /**
     * @brief The user data access object.
     */
    UserDao userDao;

public:
    /**
     * @brief Constructs a userRepository.
     */
    userRepository();
    /**
     * @brief Selects the corresponding user line.
     * @param user the userDto that contains the attributes to select the correct line.
     * @return a userdto containing correct data if the attributes exist in the table, otherwise
     * an incorrect userdto with key field set to -1.
     */
    UserDto select(UserDto user);
    /**
     * @brief Adds a line to the USER table.
     * @param user the field that contains the attributes to add
     */
    void add(UserDto user);
    /**
     * @brief Removes a line from the USER table.
     * @param key the primary key that indicates the line to remove
     */
    void remove(int key);
    /**
     * @brief Indicates if the table contains the given name.
     * @param name the name to check
     * @return true if it contains, false otherwise
     */
    bool contains(string name);
    /**
     * @brief Selects the corresponding user line.
     * @param name the name corresponding to the name attribute
     * @return a userdto containing correct data if the name exists in the table, otherwise
     * an incorrect userdto with key field set to -1.
     */
    UserDto get(string name);
    /**
     * @brief Indicates  the given name exists in the table.
     * @param name the name to check
     * @return true if exists, false otherwise
     */
    int exist(string name);
};

#endif // USERREPOSITORY_H
