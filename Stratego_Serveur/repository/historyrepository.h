#ifndef HISTORYREPOSITORY_H
#define HISTORYREPOSITORY_H
#include "dao/historyDao.h"

/**
 * @brief Represents facade class that can access to the HISTORY table.
 */
class HistoryRepository
{
private:
    /**
     * @brief Represents a history data access object.
     */
    HistoryDao historyDao;
public:
    /**
     * @brief Constructs a HistoryRepository.
     */
    HistoryRepository();
    /**
     * @brief Selects a historyDto.
     * @param hisDto the historyDto to select
     * @return a correct historyDto or an incorrect one with a -1 key.
     */
    HistoryDto select(HistoryDto hisDto);
    /**
     * @brief Adds a line to the HISTORY table.
     * @param history the history to add
     */
    void add(HistoryDto history);
    /**
     * @brief Removes a line from the HISTORY table.
     * @param key the primary key of the line to remove
     */
    void remove(int key);

    std::vector<HistoryDto> get(UserDto user1, UserDto user2);
};

#endif // HISTORYREPOSITORY_H
