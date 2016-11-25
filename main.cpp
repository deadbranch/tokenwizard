#include <iostream>
#include "CommandHandlers/GenTokenCommandHandler.h"
#include <mutex>
#include "serialization/BaseSerialization.h"
#include "TokenServer.h"
#include "ClientCommands.h"
#include "UnorderedTokenMap.h"
#include "Definitions.h"
#include "ServerResponses.h"
#include "Int32Encoder.h"
#include "RandomFiller.h"
#include "HandlerSelector.h"
#include "CommandHandlers/GetTokenCommandHandler.h"
#include <boost/thread/once.hpp>

bool myEndianness = detectEndianness();

boost::asio::io_service primary_io_service;

UnorderedTokenMap<TOKEN_LENGTH, MAP_SIZE_EXPONENT> tokenMap;
HandlerSelector handlerSelector;

StaticPacket tokenDestroyedPacket((char)ServerResponse::tokenDestroyed);
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
    tokenDestroyedPacket.serialize();
    tokenDoesNotExistPacket.serialize();

    handlerSelector.assignHandler((char)ClientCommand::getToken, new GetTokenCommandHandler());
    handlerSelector.assignHandler((char)ClientCommand::genToken, new GenTokenCommandHandler());

    string data = "123456789";
    //auto res = tokenMap.genToken(data.c_str(), data.size());
    //cout << res->tokenString->token << endl;
    int port;
    try {
        port = argc != 2 ? 10200 : std::atoi(argv[1]);
        TokenServer tokenServer(primary_io_service, port, 3);
        primary_io_service.run();
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}