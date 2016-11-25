#include "InvalidateTokenCommandHanler.h"
#include "../UnorderedTokenMap.h"
#include "../TcpSession.h"

extern StaticPacket tokenInvalidatedPacket;

void InvalidateTokenCommandHanler::Handle(char *bytes, size_t size, TcpSession &sessionContext) {
    char* token = bytes + 1;
    tokenMap.RemoveToken(token);
    sessionContext.writeStaticPacket(tokenInvalidatedPacket);
}