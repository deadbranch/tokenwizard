#include <alien.pm/tokenwizard/ClientCommands.h>
#include "GenTokenCommandHandler.h"
#include "../UnorderedTokenMap.h"
#include "../TcpSession.h"

void GenTokenCommandHandler::Handle(char *bytes, size_t size, TcpSession &sessionContext) {
    char* data = bytes + 1;
    size_t dataLength = size - 1;
    auto ptr = tokenMap.genToken(data, dataLength);
    //cout << "Generated: " << ptr->token << endl;
    ptr->writeTokenInfo(sessionContext.getPacketBuffer(TOKEN_LENGTH+8+4));
    //shared_ptr<StaticPacket> infoPtr = ptr->tokenInfo();
    //sessionContext.writeStaticPacket(*infoPtr.get());
    sessionContext.myWorker->pushRemoveTask(move(ptr));
}