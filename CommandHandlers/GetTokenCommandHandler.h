#ifndef TOKENWIZARD_GETTOKENCOMMANDHANDLER_H
#define TOKENWIZARD_GETTOKENCOMMANDHANDLER_H


#include "../CommandHandler.h"
#include "../BaseHeader.h"

class GetTokenCommandHandler: public CommandHandler {
public:
    void Handle(char* bytes, size_t size, TcpSession& sessionContext) {
        cout << "GetToken" << endl;
        char* token = bytes + 1;
        cout << token << endl;
    }
};


#endif //TOKENWIZARD_GETTOKENCOMMANDHANDLER_H
