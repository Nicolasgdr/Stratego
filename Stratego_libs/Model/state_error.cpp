#include "state_error.h"

state_error::state_error(const string& what_arg ) : logic_error(what_arg){}

state_error::state_error(const char* what_arg) : logic_error(what_arg){}
