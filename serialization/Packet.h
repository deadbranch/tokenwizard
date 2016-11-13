#ifndef TTT_SERVER_RTSVECTOR_H
#define TTT_SERVER_RTSVECTOR_H

#include "../BaseHeader.h"
#include "BaseSerialization.h"

class Packet: public vector<char> {
private:
public:
    //Packet(): vector<char>(4) {    }
    Packet(char token, size_t expectedSize = 0): vector<char>(5+expectedSize) {
        this->operator[](4) = token;
    }

    void serialize() {
        writeCount((uint32_t) (this->size() - 4), this->data());
    }
    void printPacket() {
        //cout << this->data()[5];
        /*for(int i = 0; i < this->size(); ++i) {
            cout << this->data()[i];
        }
        cout << endl;
         */
    }
    char firstChar() {
        return this->data()[5];
    }
};

#endif //TTT_SERVER_RTSVECTOR_H