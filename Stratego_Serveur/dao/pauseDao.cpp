#include <QSqlQuery>
#include "pauseDao.h"

PauseDao::PauseDao(){}

void PauseDao::insert(PauseDto item){
    QSqlQuery query;
    query.prepare("INSERT INTO PAUSE(name,gameId) values(?,?)");
    PauseDto dto = PauseDto(-1);
    query.addBindValue(item.getName());
    query.addBindValue(item.getGameId());
    qDebug()<<"insert pause "<< query.exec();
}

void PauseDao::deleteStmt(QString name, int gameId){
    QSqlQuery query;
    query.prepare("DELETE FROM PAUSE WHERE name=? AND gameId=?");
    PauseDto dto = PauseDto(-1);
    query.addBindValue(name);
    query.addBindValue(gameId);
    query.exec();
}

PauseDto PauseDao::select(int key){
    QSqlQuery query;
    query.prepare("SELECT id,name,gameId FROM PAUSE WHERE id=?");
    PauseDto stat = PauseDto(-1);
    query.addBindValue(key);
    query.exec();
    while(query.next())
    {
        stat = PauseDto(query.value(0).toInt(),query.value(1).toString(),query.value(2).toInt());
    }
    return stat;
}

PauseDto PauseDao::select(QString name, int gameId){
    QSqlQuery query;
    query.prepare("SELECT id,name,gameId FROM PAUSE WHERE name=? AND gameId=?");
    PauseDto stat = PauseDto(-1);
    query.addBindValue(name);
    query.addBindValue(gameId);
    query.exec();
    while(query.next())
    {
        stat = PauseDto(query.value(0).toInt(),query.value(1).toString(),query.value(2).toInt());
    }
    return stat;
}
