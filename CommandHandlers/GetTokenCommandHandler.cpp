#include <thread>
#include "GetTokenCommandHandler.h"
#include "../UnorderedTokenMap.h"
#include "../TcpSession.h"

extern StaticPacket tokenDoesNotExistPacket;

void GetTokenCommandHandler::Handle(char *bytes, size_t size, TcpSession &sessionContext) {
    //Deserialize
    //cout << "GetToken" << endl;
    char* token = bytes + 1;
    //cout << token << endl;
    //Handle
    auto ptr = tokenMap.try_get(token);
    if(ptr) {
//        cout << "token exists" << endl;
        sessionContext.writeStaticPacket(*ptr->dataPacket);
    }
    else {
        sessionContext.writeStaticPacket(tokenDoesNotExistPacket);
    }
}