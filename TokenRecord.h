#ifndef TOKENWIZARD_TOKENRECORD_H
#define TOKENWIZARD_TOKENRECORD_H

#include <boost/thread/pthread/once_atomic.hpp>
#include "serialization/PacketBuffer.h"
#include "serialization/StaticPacket.h"
#include "Int32Encoder.h"
#include "RandomFiller.h"
#include "ServerResponses.h"
#include "BaseHeader.h"
#include "TokenString.h"

template <size_t tokenLength>
class TokenRecord {
    boost::once_flag decreaseOnce = BOOST_ONCE_INIT;
public:
    StaticPacket* dataPacket;
    //char token[tokenLength+7];
    TokenString<tokenLength>* tokenString;
    TokenRecord(StaticPacket* _dataPacket): dataPacket(_dataPacket), tokenString(nullptr) {    }

    shared_ptr<StaticPacket> tokenInfo() {
        shared_ptr<StaticPacket> packetPtr = std::make_shared<StaticPacket>((char)ServerResponse::tokenCreated, tokenLength+7);
        memcpy(packetPtr->data()+5, tokenString->token, tokenLength + 7);
        packetPtr->serialize();
        return packetPtr;
    }

    void writeTokenInfo(PBuff* buff) {
        char* dataPtr = buff->getPtr();
        writeCount(tokenLength+8, dataPtr);
        dataPtr[4] = (char)ServerResponse::tokenCreated;
        memcpy(dataPtr+5, tokenString->token, tokenLength + 7);
        buff->currSize += tokenLength+8+4;
    }

    void generateTokenString (uint32_t offset) {
        if(tokenString)
            delete tokenString;
        tokenString = new TokenString<tokenLength>(offset);
    }

    ~TokenRecord() {
        tokenString->tryDelete();
        delete dataPacket;
    }
};

#endif //TOKENWIZARD_TOKENRECORD_H