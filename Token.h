#ifndef TOKENWIZARD_TOKENRECORD_H
#define TOKENWIZARD_TOKENRECORD_H

#include "BaseHeader.h"
#include "Int32Encoder.h"
#include "RandomFiller.h"

template <size_t tokenLength>
class Token {
public:
    Packet* data;
    char token[tokenLength+7];
    bool isEnabled = true;
    Token(uint32_t val, Packet* _dataPacket): data(_dataPacket) {
        token[tokenLength+6] = '\0';
        Int32Encoder::encode64Based(val, token);
        RandomFiller<tokenLength>::fillString(token+6);
    }
    shared_ptr<Packet> tokenInfo() {
        shared_ptr<Packet> packetPtr = std::make_shared<Packet>((char)ServerResponse::tokenCreated, tokenLength+7);
        memcpy(packetPtr->data()+5, token, tokenLength + 7);
        packetPtr->serialize();
        return packetPtr;
    }
    ~Token() {
        delete data;
    }
};

#endif //TOKENWIZARD_TOKENRECORD_H