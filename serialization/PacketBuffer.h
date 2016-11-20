#ifndef TOKENWIZARD_PACKETBUFFER_H
#define TOKENWIZARD_PACKETBUFFER_H


#include <cstdlib>
#include "BaseSerialization.h"
#include "StaticPacket.h"

class Packet {
public:
    uint32_t currSize;
    char* dataPtr;
    Packet(char *ptr) : dataPtr(ptr+4) {
    }
    void setSize(uint32_t size) {
        currSize = size;
        writeCount((uint32_t) (size), (dataPtr - 4));
    }
};

template <size_t size>
class PacketBuffer {
    char buff[size];
    bool state = false;
public:
    size_t currSize = 0;
    char* getBuff() {
        return buff;
    }
    char* getPtr() {
        return buff + currSize;
    }
    Packet beginPacket() {
        assert(!state);
        state = !state;
        return Packet(&buff[currSize]);
    }
    void endPacket(Packet& p) {
        assert(state);
        state = !state;
        int a = p.currSize;
        currSize += p.currSize+4;
    }
    size_t bytesLeft() {
        return size - currSize;
    }
    void writeStaticPacket(StaticPacket& p) {
        assert(!state);
        memcpy(&buff[currSize], p.data(), p.size());
        currSize += p.size();
    }
};

#endif //TOKENWIZARD_PACKETBUFFER_H