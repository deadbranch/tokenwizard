#ifndef TOKENWIZARD_HANDLERSELECTOR_H
#define TOKENWIZARD_HANDLERSELECTOR_H

#include <assert.h>
#include "CommandHandler.h"

class HandlerSelector {
    CommandHandler* assignedHandlers[256];
public:
    HandlerSelector() {
        for(auto i : assignedHandlers) {
            i = nullptr;
        }
    }
    void assignHandler(char token, CommandHandler *handlerPtr) {
        assert(assignedHandlers[(unsigned char)token] == nullptr);
        assignedHandlers[(unsigned char)token] = handlerPtr;
    }

    CommandHandler* getParser(char token) {
        assert(assignedHandlers[(unsigned char)token] != nullptr);
        return assignedHandlers[(unsigned char)token];
    }
};

#endif //TOKENWIZARD_HANDLERSELECTOR_H
