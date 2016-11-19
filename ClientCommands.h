#ifndef TOKENWIZARD_CLIENTCOMMANDS_H
#define TOKENWIZARD_CLIENTCOMMANDS_H


enum class ClientCommand: char {
    genToken = 0x0,
    destroyToken= 0x1,
    getToken = 0x2
};

#endif //TOKENWIZARD_CLIENTCOMMANDS_H
