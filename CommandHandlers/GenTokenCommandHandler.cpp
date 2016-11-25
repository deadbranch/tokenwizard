#include "GenTokenCommandHandler.h"
#include "../ClientCommands.h"
#include "../UnorderedTokenMap.h"
#include "../TcpSession.h"
#include "../InvalidateTask.h"

void GenTokenCommandHandler::Handle(char *bytes, size_t size, TcpSession &sessionContext) {
    char* data = bytes + 1;
    size_t dataLength = size - 1;
    auto res = tokenMap.genToken(data, dataLength);
    //cout << "Generated: " << res->tokenString->token << endl;
    res->writeTokenInfo(sessionContext.getPacketBuffer(TOKEN_LENGTH+8+4));
    sessionContext.myWorker->pushRemoveTask(res->tokenString);
}