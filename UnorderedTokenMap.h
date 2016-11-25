#ifndef TOKENWIZARD_SESSIONUNORDEREDMAP_H
#define TOKENWIZARD_SESSIONUNORDEREDMAP_H

#include "BaseHeader.h"
#include "misc/IntPow.h"
#include "ServerResponses.h"
#include "TokenRecord.h"

#include <stdlib.h>
#include "serialization/StaticPacket.h"
#include "concurrent-guard/unsafe_concurrent_guard.h"

template <int tokenLength, int mapSizeExponent>
class UnorderedTokenMap {
    unsigned int mSize;
    unsafe_concurrent_guard<TokenRecord<tokenLength>>* table;
    inline unsigned int generateOffset() {
        static thread_local unsigned int seed = (unsigned int) rand();
        return rand_r(&seed) % mSize;
    }
    //static_assert(tokenLength >= mapSizeExponent /8);
public:
    UnorderedTokenMap() {
        mSize = int_pow(2, mapSizeExponent);
        table = new unsafe_concurrent_guard<TokenRecord<tokenLength>>[mSize];
    }

    cg_shared_ptr<TokenRecord<tokenLength>> genToken(
            const char* data,
            size_t len) {
        StaticPacket* dataPacket = new StaticPacket((char)ServerResponse::tokenExists, len);
        memcpy(dataPacket->data()+5, data, len);
        char* d  = dataPacket->data()+5;
        int  a = dataPacket->size();

        dataPacket->serialize();

        TokenRecord<tokenLength>* t = new TokenRecord<tokenLength>(dataPacket);
        while(true) {
            uint offset;
            do {
                offset = generateOffset();
            } while (table[offset].is_set());
            t->generateTokenString(offset);
            unsafe_concurrent_guard<TokenRecord<tokenLength>>& guard = table[offset];
            auto ptr = guard.try_set_and_get_unsafe(t);
            if(ptr) {
                return ptr;
            }
            else {
                cout << "unsuccessful set" << endl;
            }
        }
    }

    cg_shared_ptr<TokenRecord<tokenLength>> try_get(char* token) {
        uint32_t offset = Int32Encoder::decode64Based(token);
        if(offset >= mSize)
            return nullptr;
        auto res = table[offset].try_get();
        if (res) {
            if(strcmp(token,  res->tokenString->token) != 0)
                res = nullptr;
        }
        return res;
    }

    void RemoveToken(char* token) {
        uint32_t offset = Int32Encoder::decode64Based(token);
        auto res = table[offset].try_get();
        if (res) {
            if((res->tokenString->token == token) || (strcmp(token,  res->tokenString->token) == 0))
            {
                table[offset].decrease_unsafe();
            }
        }
    }
};

#endif //TOKENWIZARD_SESSIONUNORDEREDMAP_H
