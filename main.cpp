#include <iostream>
#include <mutex>
#include "TokenServer.h"
#include "ClientCommands.h"
#include "CommandHandlers/GetTokenCommandHandler.h"
#include "CommandHandlers/GenTokenCommandHandler.h"
#include "CommandHandlers/InvalidateTokenCommandHanler.h"

bool myEndianness = detectEndianness();

boost::asio::io_service primary_io_service;

UnorderedTokenMap<TOKEN_LENGTH, MAP_SIZE_EXPONENT> tokenMap;
HandlerSelector handlerSelector;

StaticPacket tokenInvalidatedPacket((char)ServerResponse::tokenInvalidated);
StaticPacket tokenDoesNotExistPacket((char)ServerResponse::tokenDoesNotExist);

volatile char c;

class C {
public:
    C() {
        cout<< "C()" <<endl;
    }
    ~C() {
        cout<< "~C()" <<endl;
    }
};

int main(int argc, char* argv[]) {
    tokenInvalidatedPacket.serialize();
    tokenDoesNotExistPacket.serialize();

    handlerSelector.assignHandler((char)ClientCommand::getToken,
                                  new GetTokenCommandHandler());
    handlerSelector.assignHandler((char)ClientCommand::genToken,
                                  new GenTokenCommandHandler());
    handlerSelector.assignHandler((char)ClientCommand::invalidateToken,
                                  new InvalidateTokenCommandHanler());
    int port;
    try {
        port = argc != 2 ? 22200 : std::atoi(argv[1]);
        TokenServer tokenServer(primary_io_service, port, 3);
        primary_io_service.run();
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}