//
// Created by origin on 14.11.16.
//

#include <thread>
#include "GetTokenCommandHandler.h"
#include "../UnorderedTokenMap.h"
#include "../TcpSession.h"

extern Packet tokenDoesNotExistPacket;

void GetTokenCommandHandler::Handle(char *bytes, size_t size, TcpSession &sessionContext) {
    //Deserialize
    //cout << "GetToken" << endl;
    char* token = bytes + 1;
    //cout << token << endl;
    //Handle
    auto ptr = tokenMap.try_get(token);
    if(ptr && ptr->timeToDie) {
//        cout << "token exists" << endl;
        sessionContext.SendPacket<decltype(ptr)>(ptr->data, move(ptr));
    }
    else {
        cout << token << endl;
        cout << "Unknown token" << endl;
        sessionContext.SendPacket(&tokenDoesNotExistPacket);
    }
}
