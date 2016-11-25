#ifndef TOKENWIZARD_SERVERRESPONSES_H
#define TOKENWIZARD_SERVERRESPONSES_H

enum class ServerResponse: char {
    tokenCreated = 0x0,
    tokenInvalidated = 0x1,
    tokenDoesNotExist = 0x2,
    tokenExists = 0x3,
};

#endif //TOKENWIZARD_SERVERRESPONSES_H
