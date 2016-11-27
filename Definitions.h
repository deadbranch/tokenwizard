#ifndef TOKENWIZARD_DEFINES_H
#define TOKENWIZARD_DEFINES_H

#define NETWORK_ENDIANNESS __le
#define MAP_SIZE_EXPONENT 25 //the number of the elements = 2^mapSizeExponent; range: 0 < MAP_SIZE_EXPONENT < 32
#define TOKEN_LENGTH 32 //the length of the entire token
#define TOKEN_TTL 20 //time to live of a token
#define SEND_INTERVAL 25
#define DATA_LENGTH 48 //the maximum length of the token content
#define PACKET_BUFFER_SIZE 32768

#endif //TOKENWIZARD_DEFINES_H