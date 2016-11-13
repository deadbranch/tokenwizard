#include <iostream>
#include "serialization/BaseSerialization.h"
#include "TokenServer.h"
#include "ClientCommands.h"
#include "UnorderedTokenMap.h"
#include "Definitions.h"
#include "ServerResponses.h"
#include "Int32Encoder.h"
#include "RandomFiller.h"

bool myEndianness = detectEndianness();


boost::asio::io_service primary_io_service;

UnorderedTokenMap<TOKEN_LENGTH, 5> tokenMap;
Packet tokenDestroyedPacket((char)ServerResponse::tokenDestroyed);
Packet tokenDoesNotExistsPacket((char)ServerResponse::tokenDoesNotExists);

volatile char c;
int main(int argc, char* argv[]) {
    cout << time(0) << endl<<endl;
    string data = "lalkasffsdfsdfsadfsdaklfjsalkfjlsdajflsdkjfkldf";
    for(int i = 0; i < 1*1000*1000*100; ++i) {
        auto res = tokenMap.genToken(data.c_str(), data.size());
        //cout << res->token[0] << endl;
    }
    cout << c << "time " <<  time(0) << endl;
    return 0;

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