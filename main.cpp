#include <iostream>
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

bool myEndianness = detectEndianness();

boost::asio::io_service primary_io_service;

UnorderedTokenMap<TOKEN_LENGTH, 5> tokenMap;
HandlerSelector handlerSelector;

Packet tokenDestroyedPacket((char)ServerResponse::tokenDestroyed);
Packet tokenDoesNotExistsPacket((char)ServerResponse::tokenDoesNotExist);

volatile char c;
int main(int argc, char* argv[]) {
    handlerSelector.assignHandler((char)ClientCommand::getToken, new GetTokenCommandHandler());
    string data = "lalkasffsdfsdfsadfsdaklfjsalkfjlsdajflsdkjfkldf";
    auto res = tokenMap.genToken(data.c_str(), data.size());
    cout << res->token << endl;

    try {
        if (argc != 2) {
            std::cerr << "Port is non set\n";
            return 1;
        }
        TokenServer tokenServer(primary_io_service, static_cast<short>(std::atoi(argv[1])));
        primary_io_service.run();
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}