#ifndef TOKENWIZARD_GENTOKEN_H
#define TOKENWIZARD_GENTOKEN_H

#include "BaseHeader.h"
#include "Definitions.h"

extern const char alphabet[63];

template <int length>
class RandomFiller {
public:
    static void fillString(char *destination);
};

template <int length>
void RandomFiller<length>::fillString(char *destination) {
    static thread_local unsigned int seed = (unsigned int) rand();
    for(char* lastChar = destination + length; destination < lastChar; ++destination)
        *destination = alphabet[rand_r(&seed)%62];
}

#endif //TOKENWIZARD_GENTOKEN_H
