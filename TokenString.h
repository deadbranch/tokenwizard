#ifndef TOKENWIZARD_TOKENSTRING_H
#define TOKENWIZARD_TOKENSTRING_H

#include <atomic>
#include <cstdio>
#include "Int32Encoder.h"
#include "RandomFiller.h"

template <size_t tokenLength>
struct TokenString {
public:
    atomic_flag mDeleteTwiceFlag;
    char token[tokenLength+7];

    TokenString(uint32_t offset): mDeleteTwiceFlag(false) {
        Int32Encoder::encode64Based(offset, token);
        RandomFiller<tokenLength>::fillString(token+6);
        token[tokenLength+6] = '\0';
    }

    void tryDelete() {
        if(mDeleteTwiceFlag.test_and_set(memory_order_acq_rel))
            delete this;
    }

    ~TokenString() {
    }
};

#endif //TOKENWIZARD_TOKENSTRING_H