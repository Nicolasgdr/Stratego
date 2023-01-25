#include "userrepository.h"

userRepository::userRepository(): userDao(UserDao())
{}

UserDto userRepository::select(UserDto user)
{
    return userDao.select(user.getKey());
}

void userRepository::add(UserDto user)
{
    if(!contains(user.getName()))
    {
        userDao.insert(user);
    }
}

void userRepository::remove(int key)
{
    userDao.deleteStmt(key);
}

bool userRepository::contains(string name)
{
    UserDto user = userDao.select(name);
    return user.getKey()!=-1;
}

UserDto userRepository::get(string name)
{
    return userDao.select(name);
}

int userRepository::exist(string name){
    return userDao.exist(name);
}
