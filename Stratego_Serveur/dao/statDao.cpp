#include "statDao.h"

StatDao::StatDao(){}

void StatDao::insert(StatDto item){
    QSqlQuery query;
    query.prepare("INSERT INTO STAT(name,nbVictory) values(?,?)");
    StatDto dto = StatDto(-1);
    QString name = QString::fromStdString(item.getName());
    query.addBindValue(name);
    query.addBindValue(item.getNbVictory());
    query.exec();
    //exception!
}

int StatDao::getNbVictory(string name){
   QSqlQuery query;
   query.prepare("SELECT COUNT(*) FROM HISTORY H INNER JOIN STAT S ON H.winner = S.name WHERE H.winner=?");
   QString qName = QString::fromStdString(name);
   query.addBindValue(qName);
   if(!query.exec()){
       qDebug() << "false exec";
   }
   if(!query.first()){
       qDebug() << "false first";
   }
   return query.value(0).toInt();
}

void StatDao::deleteStmt(int key){
    QSqlQuery query;
    query.prepare("DELETE FROM STAT WHERE id = ?");
    query.addBindValue(key);
    query.exec();
}

void StatDao::update(StatDto item){
    QSqlQuery query;
    query.prepare("UPDATE STAT SET name=?, nbVictory=? where id=?");
    QString value = QString::fromStdString(item.getName());
    query.addBindValue(value);
    query.addBindValue(item.getNbVictory());
    query.addBindValue(item.getKey());
    query.exec();
}

vector<StatDto> StatDao::selectAll(){
    QSqlQuery query;
    query.prepare("SELECT id, name, nbVictory FROM STAT");
    vector<StatDto> stats;
    query.exec();
    //exception!
    while(query.next()){
        StatDto stat = StatDto(query.value(0).toInt(),query.value(1).toString().toStdString(),query.value(2).toInt());
        stats.push_back(stat);
    }
    return stats;
}

StatDto StatDao::select(int key){
    QSqlQuery query;
    query.prepare("SELECT id, name, nbVictory FROM STAT WHERE id = ?");
    StatDto stat = StatDto(-1);
    query.addBindValue(key);
    query.exec();
    //exception!
    while(query.next())
    {
        stat = StatDto(query.value(0).toInt(),query.value(1).toString().toStdString(),query.value(2).toInt());
    }
    return stat;
}

StatDto StatDao::select(string name){
    QSqlQuery query;
    query.prepare("SELECT id, name, nbVictory FROM STAT WHERE name = ?");
    StatDto stat = StatDto(-1);
    QString value = QString::fromStdString(name);
    query.addBindValue(value);
    query.exec();
    //exception
    while(query.next())
    {
        stat = StatDto(query.value(0).toInt(), query.value(1).toString().toStdString(),query.value(2).toInt());
    }
    return stat;
}
