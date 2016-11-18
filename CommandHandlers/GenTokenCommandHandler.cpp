#include "GenTokenCommandHandler.h"
#include "../UnorderedTokenMap.h"
#include "../TcpSession.h"

void GenTokenCommandHandler::Handle(char *bytes, size_t size, TcpSession &sessionContext) {
    char* data = bytes + 1;
    size_t dataLength = size - 1;
    auto ptr = tokenMap.genToken(bytes, dataLength);
    shared_ptr<Packet> infoPtr = ptr->tokenInfo();
    sessionContext.SendPacket<shared_ptr<Packet>>(infoPtr.get(), move(infoPtr));
}