#ifndef HISTORYDTO_H
#define HISTORYDTO_H
#include "dto/userDto.h"

/**
 * @brief Represents a history data transfer object.
 */
class HistoryDto
{
private:
    /**
     * @brief The key
     */
    int _key;
    /**
     * @brief First user
     */
    UserDto _user1;
    /**
     * @brief Second user
     */
    UserDto _user2;
    /**
     * @brief Winner of the game
     */
    string _winner;

public:
    /**
     * @brief Constructs a HistoryDto from the given key.
     * @param key the primary key
     */
    HistoryDto(int key);
    /**
     * @brief Constructs HistoryDto.
     * @param key the primary key
     * @param user1 the first user
     * @param user2 the second user
     * @param winner the winner
     */
    HistoryDto(int key, UserDto user1, UserDto user2,string winner);
    /**
     * @brief Constructs HistoryDto.
     * @param user1 the first user
     * @param user2 the second user
     * @param winner the winner
     */
    HistoryDto(UserDto user1, UserDto user2,string winner);
    /**
     * @brief Gets the key
     * @return an integer that is the key field
     */
    int getKey()const;
    /**
     * @brief Gets the first user
     * @return a UserDto
     */
    UserDto getUser1()const;
    /**
     * @brief Gets the second user
     * @return a UserDto
     */
    UserDto getUser2()const;
    /**
     * @brief Gets the winner
     * @return a UserDto
     */
    string getWinner()const;

};

#endif // HISTORYDTO_H
