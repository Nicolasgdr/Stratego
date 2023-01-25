#include "pauseDto.h"

PauseDto::PauseDto(int key):_key(key){}

PauseDto::PauseDto(QString name, int gameId):_name(name),gameId(gameId){}

PauseDto::PauseDto(int key, QString name, int gameId):_key(key),_name(name),gameId(gameId){}

/**
 * @brief get Key.
 * @return primary id.
 */
int PauseDto::getKey()const{
    return _key;
}

/**
 * @brief get name of user.
 * @return name of user.
 */
QString PauseDto::getName()const{
    return _name;
}

int PauseDto::getGameId()const{
    return gameId;
}
