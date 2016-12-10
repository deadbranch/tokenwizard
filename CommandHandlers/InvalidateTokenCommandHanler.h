#ifndef TOKENWIZARD_INVALIDATETOKENCOMMANDHANLER_H
#define TOKENWIZARD_INVALIDATETOKENCOMMANDHANLER_H

#include "../CommandHandler.h"
#include "../Definitions.h"

template <int tokenLength, int mapSizeExponent>
class UnorderedTokenMap;

extern UnorderedTokenMap<TOKEN_LENGTH, MAP_SIZE_EXPONENT> tokenMap;

class InvalidateTokenCommandHanler: public CommandHandler {
public:
    void Handle(char* bytes, size_t size, TcpSession& sessionContext);
};

#endif //TOKENWIZARD_INVALIDATETOKENCOMMANDHANLER_H
