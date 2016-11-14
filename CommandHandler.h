#ifndef TOKENWIZARD_COMMANDHANDLER_H
#define TOKENWIZARD_COMMANDHANDLER_H

#include <cstdlib>

class TcpSession;

class CommandHandler {
public:
    virtual void Handle(char* bytes, size_t size, TcpSession& sessionContext) = 0;
};

#endif //TOKENWIZARD_COMMANDHANDLER_H
