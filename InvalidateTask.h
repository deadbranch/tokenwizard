#ifndef TOKENWIZARD_REMOVETASK_H
#define TOKENWIZARD_REMOVETASK_H

#include <ctime>
#include "TokenString.h"

template <size_t  tokenLength>
class InvalidateTask {
public:
    time_t deleteTime;
    TokenString* tokenString;
    InvalidateTask(TokenString tokenString): tokenString(tokenString) {
        deleteTime = std::time(0);
    }
};

#endif //TOKENWIZARD_REMOVETASK_H
