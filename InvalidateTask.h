#ifndef TOKENWIZARD_REMOVETASK_H
#define TOKENWIZARD_REMOVETASK_H

#include <ctime>
#include "UnorderedTokenMap.h"
#include "TokenString.h"

extern UnorderedTokenMap<TOKEN_LENGTH, MAP_SIZE_EXPONENT> tokenMap;

template <size_t  tokenLength>
class InvalidateTask {
public:
    time_t deleteTime;
    TokenString<tokenLength>* tokenString;
    InvalidateTask(TokenString<tokenLength>* tokenString, uint32_t lifeTime): tokenString(tokenString) {
        deleteTime = std::time(0) + lifeTime;
    }
    ~InvalidateTask() {
        tokenMap.RemoveToken(tokenString->token);
        tokenString->tryDelete();
    }
};

#endif //TOKENWIZARD_REMOVETASK_H
