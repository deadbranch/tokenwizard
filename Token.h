#ifndef TOKENWIZARD_TOKENRECORD_H
#define TOKENWIZARD_TOKENRECORD_H

#include <boost/thread/pthread/once_atomic.hpp>
#include "serialization/PacketBuffer.h"
#include "serialization/StaticPacket.h"
#include "Int32Encoder.h"
#include "RandomFiller.h"
#include "ServerResponses.h"
#include "BaseHeader.h"

template <size_t tokenLength>
class Token {
    boost::once_flag decreaseOnce = BOOST_ONCE_INIT;
public:
    StaticPacket* dataPacket;
    char token[tokenLength+7];
    time_t timeToDie;

    Token(uint32_t val, StaticPacket* _dataPacket): dataPacket(_dataPacket) {
        timeToDie = time(0) + TOKEN_TTL;
        token[tokenLength+6] = '\0';
        Int32Encoder::encode64Based(val, token);
        RandomFiller<tokenLength>::fillString(token+6);
    }

    shared_ptr<StaticPacket> tokenInfo() {
        shared_ptr<StaticPacket> packetPtr = std::make_shared<StaticPacket>((char)ServerResponse::tokenCreated, tokenLength+7);
        memcpy(packetPtr->data()+5, token, tokenLength + 7);
        packetPtr->serialize();
        return packetPtr;
    }

    void writeTokenInfo(PBuff* buff) {
        char* dataPtr = buff->getPtr();
        writeCount(tokenLength+8, dataPtr);
        dataPtr[4] = (char)ServerResponse::tokenCreated;
        memcpy(dataPtr+5, token, tokenLength + 7);
        buff->currSize += tokenLength+8+4;
    }

    ~Token() {
        delete dataPacket;
    }
};

#endif //TOKENWIZARD_TOKENRECORD_H