#ifndef USERDTO_H
#define USERDTO_H

#include <string>

using namespace std;

/**
* @brief Represents a user data transfer object.
*/
class UserDto
{

private:
    /**
     * @brief The primary key
     */
    int _key;
    /**
     * @brief The name of the user
     */
    string _name;

public:
    /**
     * @brief Constructs a UserDto.
     * @param key the primary id.
     */
    UserDto(int key);
    /**
     * @brief Constructs a UserDto.
     * @param key the primary id.
     * @param name the name of the user.
     */
    UserDto(int key, string name);
    /**
     * @brief Constructs a UserDto.
     * @param name the name of the user.
     */
    UserDto(string name);
    /**
     * @brief get Key.
     * @return primary id.
     */
    int getKey()const;
    /**
     * @brief get name of user.
     * @return name of user.
     */
    string getName()const;
    /**
     * @brief set name for user
     * @param name of user.
     */
    void setName(string name);

};

#endif // USERDTO_H
