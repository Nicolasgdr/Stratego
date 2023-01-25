#include "userDto.h"

UserDto::UserDto(int key)
{
    this->_key = key;
}

UserDto::UserDto(int key, string name){
    this->_key = key;
    this->_name = name;
}

UserDto::UserDto(string name){
    this->_name = name;
}

int UserDto::getKey()const{
    return this->_key;
}

string UserDto::getName()const{
    return this->_name;
}

void UserDto::setName(string name){
    this->_name = name;
}
