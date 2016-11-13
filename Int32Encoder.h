#ifndef TOKENWIZARD_INT32ENCODER_H
#define TOKENWIZARD_INT32ENCODER_H

#include "BaseHeader.h"
#include "serialization/Packet.h"

class Int32Encoder {
    static char encodeMap[];
    static uint decodeMap[];
public:
    Int32Encoder() {
        decodeMap['a']=0;
        decodeMap['b']=1;
        decodeMap['c']=2;
        decodeMap['d']=3;
        decodeMap['e']=4;
        decodeMap['f']=5;
        decodeMap['g']=6;
        decodeMap['h']=7;
        decodeMap['i']=8;
        decodeMap['j']=9;
        decodeMap['k']=10;
        decodeMap['l']=11;
        decodeMap['m']=12;
        decodeMap['n']=13;
        decodeMap['o']=14;
        decodeMap['p']=15;
        decodeMap['q']=16;
        decodeMap['r']=17;
        decodeMap['s']=18;
        decodeMap['t']=19;
        decodeMap['u']=20;
        decodeMap['v']=21;
        decodeMap['w']=22;
        decodeMap['x']=23;
        decodeMap['y']=24;
        decodeMap['z']=25;
        decodeMap['A']=26;
        decodeMap['B']=27;
        decodeMap['C']=28;
        decodeMap['D']=29;
        decodeMap['E']=30;
        decodeMap['F']=31;
        decodeMap['G']=32;
        decodeMap['H']=33;
        decodeMap['I']=34;
        decodeMap['J']=35;
        decodeMap['K']=36;
        decodeMap['L']=37;
        decodeMap['M']=38;
        decodeMap['N']=39;
        decodeMap['O']=40;
        decodeMap['P']=41;
        decodeMap['Q']=42;
        decodeMap['R']=43;
        decodeMap['S']=44;
        decodeMap['T']=45;
        decodeMap['U']=46;
        decodeMap['V']=47;
        decodeMap['W']=48;
        decodeMap['X']=49;
        decodeMap['Y']=50;
        decodeMap['Z']=51;
        decodeMap['0']=52;
        decodeMap['1']=53;
        decodeMap['2']=54;
        decodeMap['3']=55;
        decodeMap['4']=56;
        decodeMap['5']=57;
        decodeMap['6']=58;
        decodeMap['7']=59;
        decodeMap['8']=60;
        decodeMap['9']=61;
        decodeMap['-']=62;
        decodeMap['_']=63;
    }

    static inline void encode64Based(uint32_t val, char* destination) {
        char* lastChar = destination + 6;
        while(val) {
            uint remainder = val % 64;
            *destination = encodeMap[remainder];
            val = val / 64;
            ++destination;
        }
        for(; destination < lastChar; ++destination)
            *destination = 'a';
    }

    static inline uint32_t decode64Based(const char* ptr){
        uint res = 0;
        uint factor = 1;
        static uint maxFactor = 64*64*64*64*64;
        while(true)
        {
            res += decodeMap[*ptr] * factor;
            ++ptr;
            if(factor == maxFactor)
                break;
            factor *= 64;
        }
        return res;
    }
};

#endif //TOKENWIZARD_INT32ENCODER_H
