#include "statrepository.h"

statRepository::statRepository():statDao(StatDao())
{}

StatDto statRepository::select(StatDto stat)
{
    return statDao.select(stat.getKey());
}

void statRepository::add(StatDto stat)
{
        statDao.insert(stat);
}

void statRepository::remove(int key)
{
    statDao.deleteStmt(key);
}

StatDto statRepository::get(string name)
{
    return statDao.select(name);
}

void statRepository::update(StatDto stat){
    statDao.update(stat);
}

int statRepository::getNbVictory(string name){
    return statDao.getNbVictory(name);
}
