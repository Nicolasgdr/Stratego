#ifndef STATDTO_H
#define STATDTO_H
#include <string>

using namespace std;

/**
* @brief Represents a stat data transfer object.
*/
class StatDto
{
private:
    /**
     * @brief The key of the object
     */
    int _key;
    /**
     * @brief The name of the user
     */
    string _name;
    /**
     * @brief The number of victories of a user
     */
    int _nbVictory;

public:
    /**
     * @brief Constructs a StatDto.
     * @param key the primary id.
     */
    StatDto(int key);
    /**
     * @brief Constructs a StatDto.
     * @param name the name of the user.
     * @param nbVictory the number of user's victories.
     */
    StatDto(string name, int nbVictory);

    /**
     * @brief Constructs a StatDto.
     * @param key the primary id.
     * @param name the name of the user.
     * @param nbVictory the number of user's victories.
     */
    StatDto(int key, string name, int nbVictory);

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
     * @brief get Number of Victory.
     * @return number of victory of player.
     */
    int getNbVictory()const;

    /**
     * @brief set name for user
     * @param name of user.
     */
    void setName(string name);

    /**
     * @brief set number of victory.
     * @param number of victory.
     */
    void setNbVictory(int nbVictory);
};

#endif // STATDTO_H
