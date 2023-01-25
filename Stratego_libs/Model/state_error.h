#ifndef STATE_ERROR_H
#define STATE_ERROR_H

#include <stdexcept>

using namespace std;

/**
 * @brief Exception to be throw if the current state is not the expected state.
 * @details Extending logic_error from stdexcept.
 */
class state_error : public logic_error
{public:
    /**
     * @brief Builds a state_error with given message.
     * @param what_arg The error message.
     */
    state_error(const string& what_arg );

    /**
     * @brief Builds a state_error with given message.
     * @param what_arg The error message.
     */
    state_error(const char* what_arg);
};

#endif // STATE_ERROR_H
