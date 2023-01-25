#include "historyrepository.h"

HistoryRepository::HistoryRepository():historyDao(HistoryDao()){
}

HistoryDto HistoryRepository::select(HistoryDto hDto)
{
    return historyDao.select(hDto.getKey());
}

void HistoryRepository::add(HistoryDto item)
{
    historyDao.insert(item);
}

void HistoryRepository::remove(int key)
{
    historyDao.deleteStmt(key);
}

std::vector<HistoryDto> HistoryRepository::get(UserDto user1, UserDto user2)
{
    return historyDao.selectAll(user1,user2);
}
