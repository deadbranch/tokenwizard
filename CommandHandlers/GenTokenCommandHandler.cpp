#include "GenTokenCommandHandler.h"
#include "../ClientCommands.h"
#include "../UnorderedTokenMap.h"
#include "../TcpSession.h"
#include "../InvalidateTask.h"

void GenTokenCommandHandler::Handle(char *bytes, size_t size, TcpSession &sessionContext) {
    uint32_t lifeTime = getDeserializedUInt32(bytes + 1);
    char* data = bytes + 1+4;
    size_t dataLength = size - 1 - 4;
    auto res = tokenMap.genToken(data, dataLength);
    cout << "Generated: " << res->tokenString->token << endl;
    res->writeTokenInfo(sessionContext.getPacketBuffer(TOKEN_LENGTH+8+4));
    sessionContext.myWorker->pushRemoveTask(res->tokenString, lifeTime);
}