#include "historyDto.h"

HistoryDto::HistoryDto(int key):_key(key),_user1(UserDto(-1)),_user2(UserDto(-1)){}

HistoryDto::HistoryDto(int key, UserDto user1, UserDto user2,string winner):_key(key),
                       _user1(UserDto(user1)),
    _user2(UserDto(user2)),_winner(winner){}

HistoryDto::HistoryDto(UserDto user1, UserDto user2,string winner):
                       _user1(UserDto(user1)),
    _user2(UserDto(user2)),_winner(winner){}

int HistoryDto::getKey()const{
    return this->_key;
}

UserDto HistoryDto::getUser1()const{
    return this->_user1;
}

UserDto HistoryDto::getUser2()const{
    return this->_user2;
}

string HistoryDto::getWinner()const{
    return this->_winner;
}
