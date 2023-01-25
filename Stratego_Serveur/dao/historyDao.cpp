#include "historyDao.h"

HistoryDao::HistoryDao(){}

void HistoryDao::insert(HistoryDto history)
{
   QSqlQuery query;
   query.prepare("INSERT INTO HISTORY(user1,user2,"
                 "winner) values(?,?,?)");
   QString winner = QString::fromStdString(history.getWinner());
   query.addBindValue(history.getUser1().getKey());
   query.addBindValue(history.getUser2().getKey());
   query.addBindValue(winner);
   if(!query.exec())
   {
       throw invalid_argument("Error "+query.lastError().text().toStdString());
   }
}

void HistoryDao::deleteStmt(int key)
{
    QSqlQuery query;
    query.prepare("DELETE FROM HISTORY WHERE id = ?");
    query.addBindValue(key);
    if(!query.exec())
    {
        throw invalid_argument("Error "+query.lastError().text().toStdString());
    }
}

void HistoryDao::update(HistoryDto history)
{
    QSqlQuery query;
    query.prepare("UPDATE HISTORY SET user1=?, user2=?,"
                  "winner=?, where id=?");
    QString winner = QString::fromStdString(history.getWinner());
    query.addBindValue(history.getUser1().getKey());
    query.addBindValue(history.getUser2().getKey());
    query.addBindValue(winner);
    query.addBindValue(history.getKey());
    if(!query.exec())
    {
       throw invalid_argument("Error "+query.lastError().text().toStdString());
    }
}

vector<HistoryDto> HistoryDao::selectAll()
{
    QSqlQuery query;
    query.prepare("SELECT id,user1,user2,"
                  "(SELECT p.name FROM USER u WHERE p.id = h.user1) name1,"
                  "(SELECT p.name FROM USER u WHERE p.id = h.user2) name2,"
                  "winner FROM HISTORY h");
    vector<HistoryDto> historys;
    if(!query.exec())
    {
        throw invalid_argument("Error "+query.lastError().text().toStdString());
    }
    while(query.next())
    {
        UserDto user1 = UserDto(query.value(1).toInt(),query.value(3).toString().toStdString());
        UserDto user2 = UserDto(query.value(2).toInt(),query.value(4).toString().toStdString());
        HistoryDto his = HistoryDto(query.value(0).toInt(), user1, user2, query.value(5).toString().toStdString());
        historys.push_back(his);
    }
    return historys;
}

HistoryDto HistoryDao::select(int key)
{
    QSqlQuery query;
    query.prepare("SELECT id,user1,user2,"
                  "(SELECT p.name FROM USER u WHERE p.id = h.user1) name1,"
                  "(SELECT p.name FROM USER u WHERE p.id = h.user2) name2,"
                  "winner FROM HISTORY h");
    HistoryDto hisdto = HistoryDto(-1);
    query.addBindValue(key);
    if(!query.exec())
    {
        throw invalid_argument("Error "+query.lastError().text().toStdString());
    }
    while(query.next())
    {
        UserDto user1 = UserDto(query.value(1).toInt(),query.value(3).toString().toStdString());
        UserDto user2 = UserDto(query.value(2).toInt(),query.value(4).toString().toStdString());
        HistoryDto his = HistoryDto(query.value(0).toInt(), user1, user2, query.value(5).toString().toStdString());
    }
    return hisdto;
}

vector<HistoryDto> HistoryDao::selectAll(UserDto user1, UserDto user2)
{
    QSqlQuery query;
    query.prepare("SELECT id,user1,user2,"
                  "(SELECT p.name FROM USER u WHERE p.id = h.user1) name1,"
                  "(SELECT p.name FROM USER u WHERE p.id = h.user2) name2,"
                  "winner FROM HISTORY h"
                  "WHERE (user1 = ? AND user2 = ?) OR (user1 = ? AND user2 = ?) ORDER BY id DESC");
    vector<HistoryDto> historys;
    query.addBindValue(user1.getKey());
    query.addBindValue(user2.getKey());
    query.addBindValue(user2.getKey());
    query.addBindValue(user1.getKey());
    if(!query.exec())
    {
        throw invalid_argument("Error "+query.lastError().text().toStdString());
    }
    while(query.next())
    {
        HistoryDto his = HistoryDto(query.value(0).toInt(), user1, user2, query.value(5).toString().toStdString());
        historys.push_back(his);
    }
    return historys;
}
