//
// Created by origin on 14.11.16.
//

#include "GetTokenCommandHandler.h"
#include "../UnorderedTokenMap.h"
#include "../TcpSession.h"

extern Packet tokenDoesNotExistsPacket;

void GetTokenCommandHandler::Handle(char *bytes, size_t size, TcpSession &sessionContext) {
    //Deserialize
    cout << "GetToken" << endl;
    char* token = bytes + 1;
    cout << token << endl;

    //Handle
    auto ptr = tokenMap.try_get(token);
    if(ptr) {
        cout << "token exists" << endl;
        sessionContext.SendPacket<decltype(ptr)>(ptr->data, move(ptr));
    }
    else {
        cout << "Unknown token" << endl;
        sessionContext.SendPacket(&tokenDoesNotExistsPacket);
    }
}
