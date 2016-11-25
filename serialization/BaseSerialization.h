#ifndef TOKENWIZARD_BASESERIALIZATION_H
#define TOKENWIZARD_BASESERIALIZATION_H

#include <cstdint>
#include "../Definitions.h"
#define __le false
#define __be true

#include "../BaseHeader.h"
extern bool myEndianness;

inline bool detectEndianness() {
    int test_var = 1;
    unsigned char* test_endian = (unsigned char*)&test_var;
    return (test_endian[0] == 0);
}

inline uint32_t reverseInt32(uint32_t i) {
    return ((i>>24)&0xff) |
    ((i<<8)&0xff0000) |
    ((i>>8)&0xff00) |
    ((i<<24)&0xff000000);
}

inline uint32_t fixEndianness(uint32_t val) {
    return (myEndianness == NETWORK_ENDIANNESS) ? val : reverseInt32(val);
}

inline void writeCount(uint32_t count, char* buf) {
    *reinterpret_cast<uint32_t *>(buf) = fixEndianness(count);
}

inline uint32_t getDeserializedUInt32_unsafe(char *dataPtr) {
    //assert((reinterpret_cast<intptr_t>(dataPtr) % 4) == 0);
    return fixEndianness(*reinterpret_cast<uint32_t *>(dataPtr));
}

inline uint32_t getDeserializedUInt32(char *dataPtr) {
    char tmpbuf[4];
    tmpbuf[0] = dataPtr[0];
    tmpbuf[1] = dataPtr[1];
    tmpbuf[2] = dataPtr[2];
    tmpbuf[3] = dataPtr[3];
    //assert((reinterpret_cast<intptr_t>(dataPtr) % 4) == 0);
    return fixEndianness(*reinterpret_cast<uint32_t *>(tmpbuf));
}


#endif