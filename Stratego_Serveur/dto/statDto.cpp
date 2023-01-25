#include "statDto.h"

StatDto::StatDto(int key){
    this->_key = key;
}

StatDto::StatDto(string name, int nbVictory){
    this->_name = name;
    this->_nbVictory = nbVictory;
}

StatDto::StatDto(int key, string name, int nbVictory){
    this->_key = key;
    this->_name = name;
    this->_nbVictory = nbVictory;
}

int StatDto::getKey()const{
    return this->_key;
}

string StatDto::getName()const{
    return this->_name;
}

int StatDto::getNbVictory()const{
    return this->_nbVictory;
}

void StatDto::setName(string name){
    this->_name = name;
}

void StatDto::setNbVictory(int nbVictory){
    this->_nbVictory = nbVictory;
}
