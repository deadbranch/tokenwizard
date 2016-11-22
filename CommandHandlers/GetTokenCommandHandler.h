#ifndef TOKENWIZARD_GETTOKENCOMMANDHANDLER_H
#define TOKENWIZARD_GETTOKENCOMMANDHANDLER_H

#include "../CommandHandler.h"
#include "../BaseHeader.h"
#include "../Definitions.h"

template <int tokenLength, int mapSizeExponent>
class UnorderedTokenMap;

extern UnorderedTokenMap<TOKEN_LENGTH, MAP_SIZE_EXPONENT> tokenMap;

class GetTokenCommandHandler: public CommandHandler {
public:
    void Handle(char* bytes, size_t size, TcpSession& sessionContext);
};

#endif //TOKENWIZARD_GETTOKENCOMMANDHANDLER_H
