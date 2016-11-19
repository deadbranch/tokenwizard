#ifndef TOKENWIZARD_SESSIONUNORDEREDMAP_H
#define TOKENWIZARD_SESSIONUNORDEREDMAP_H

#include "BaseHeader.h"
#include "serialization/Packet.h"
#include "misc/IntPow.h"
#include "ServerResponses.h"
#include "Token.h"

#include <stdlib.h>

template <int tokenLength, int mapSizeExponent>
class UnorderedTokenMap {
    unsigned int mSize;
    concurrent_guard<Token<tokenLength>>* table;
    inline unsigned int generateOffset() {
        static thread_local unsigned int seed = (unsigned int) rand();
        return rand_r(&seed) % mSize;
    }
    //static_assert(tokenLength >= mapSizeExponent /8);
public:
    UnorderedTokenMap() {
        mSize = int_pow(2, mapSizeExponent);
        table = new concurrent_guard<Token<tokenLength>>[mSize];
    }
    cg_shared_ptr<Token<tokenLength>> genToken(const char* data, size_t len) {
        Packet* dataPacket = new Packet((char)ServerResponse::tokenExists, len);
        memcpy(dataPacket->data()+5, data, len);
        char* d  = dataPacket->data()+5;
        dataPacket->serialize();

        while(true) {
            uint offset;
            do {
                offset = generateOffset();
            } while (table[offset].is_set());
            Token<tokenLength>* t = new Token<tokenLength>(offset, dataPacket);
            concurrent_guard<Token<tokenLength>>& guard = table[offset];
            auto ptr = guard.try_set(t);
            if(ptr){
                return ptr;
            }
            else {
                delete t;
                cout << "unsuccessful set" << endl;
            }
        }
    }

    cg_shared_ptr<Token<tokenLength>> try_get(char* token) {
        uint32_t offset = Int32Encoder::decode64Based(token);
        if(offset >= mSize)
            return nullptr;
        auto res = table[offset].try_get();
        if (res) {
            if(strcmp(token,  res->token) != 0)
                res = nullptr;
        }
        return res;
    }
};

#endif //TOKENWIZARD_SESSIONUNORDEREDMAP_H
