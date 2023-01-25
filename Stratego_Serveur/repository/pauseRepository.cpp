#include "pauseRepository.h"

void PauseRepository::add(PauseDto item){
    pDao.insert(item);
}

void PauseRepository::deleteStmt(QString name, int gameId){
    pDao.deleteStmt(name,gameId);
}

PauseDto PauseRepository::select(int key){
    return pDao.select(key);
}

PauseDto PauseRepository::select(QString name, int gameId){
    return pDao.select(name,gameId);
}
