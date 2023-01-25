#include "userDao.h"

UserDao::UserDao(){}

void UserDao::insert(UserDto item){
    QSqlQuery query;
    query.prepare("INSERT INTO USER(name) values(?)");
    UserDto dto = UserDto(-1);
    QString value = QString::fromStdString(item.getName());
    query.addBindValue(value);
    query.exec();
    //exception!
}

void UserDao::deleteStmt(int key){
    QSqlQuery query;
    query.prepare("DELETE FROM USER WHERE id = ?");
    query.addBindValue(key);
    query.exec();
}

void UserDao::update(UserDto item){
    QSqlQuery query;
    query.prepare("UPDATE USER SET name=? where id=?");
    QString value = QString::fromStdString(item.getName());
    query.addBindValue(value);
    query.addBindValue(item.getKey());
    query.exec();
}

vector<UserDto> UserDao::selectAll(){
    QSqlQuery query;
    query.prepare("SELECT id, name FROM USER");
    vector<UserDto> users;
    query.exec();
    //exception!
    while(query.next()){
        UserDto user = UserDto(query.value(0).toInt(),query.value(1).toString().toStdString());
        users.push_back(user);
    }
    return users;
}

UserDto UserDao::select(int key){
    QSqlQuery query;
    query.prepare("SELECT id, name FROM USER WHERE id = ?");
    UserDto user = UserDto(-1);
    query.addBindValue(key);
    query.exec();
    //exception!
    while(query.next())
    {
        user = UserDto(query.value(0).toInt(),query.value(1).toString().toStdString());
    }
    return user;
}

UserDto UserDao::select(string name){
    QSqlQuery query;
    query.prepare("SELECT id, name FROM USER WHERE name = ?");
    UserDto user = UserDto(-1);
    QString value = QString::fromStdString(name);
    query.addBindValue(value);
    query.exec();
    //exception
    while(query.next())
    {
        user = UserDto(query.value(0).toInt(), query.value(1).toString().toStdString());
    }
    return user;
}

int UserDao::exist(string name){
    QSqlQuery query;
    query.prepare("SELECT count(*) FROM USER WHERE name = ?");
    UserDto user = UserDto(-1);
    QString value = QString::fromStdString(name);
    query.addBindValue(value);
    if(!query.exec()){
       qDebug() << "false exec";
    }
    if(!query.first()){
       qDebug() << "false first";
    }
    return query.value(0).toInt();
}
