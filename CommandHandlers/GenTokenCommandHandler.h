#ifndef TOKENWIZARD_GENTOKENCOMMANDHANDLER_H
#define TOKENWIZARD_GENTOKENCOMMANDHANDLER_H

#include "../CommandHandler.h"
#include "../BaseHeader.h"
#include "../Definitions.h"

template <int tokenLength, int mapSizeExponent>
class UnorderedTokenMap;

extern UnorderedTokenMap<TOKEN_LENGTH, MAP_SIZE_EXPONENT> tokenMap;

class GenTokenCommandHandler: public CommandHandler {
public:
    void Handle(char* bytes, size_t size, TcpSession& sessionContext);
};

#endif //TOKENWIZARD_GENTOKENCOMMANDHANDLER_H
