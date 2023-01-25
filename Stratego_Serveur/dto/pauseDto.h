#ifndef PAUSEDTO_H
#define PAUSEDTO_H

#include <QString>

/**
 * @brief Represents a pause data transfer object.
 */
class PauseDto
{
private:
    /**
     * @brief The key
     */
    int _key;
    /**
     * @brief The name of the client that makes a pause
     */
    QString _name;
    /**
     * @brief The game id of the game in a pause state
     */
    int gameId;

public:
    /**
     * @brief Construct a PauseDto.
     * @param key the key
     */
    PauseDto(int key);
    /**
     * @brief Constructs a PauseDto.
     * @param name the name of the player
     * @param gameId the game id to make a pause to
     */
    PauseDto(QString name, int gameId);
    /**
     * @brief Constructs a PauseDto.
     * @param key the key
     * @param name the name of the player
     * @param gameId the game id to make a pause to
     */
    PauseDto(int key, QString name, int gameId);
    /**
     * @brief get Key.
     * @return primary id.
     */
    int getKey()const;
    /**
     * @brief get name of user.
     * @return name of user.
     */
    QString getName()const;
    /**
     * @brief Gets the game id.
     * @return the game id.
     */
    int getGameId()const;
};

#endif // PAUSEDTO_H
