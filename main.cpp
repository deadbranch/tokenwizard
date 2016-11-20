#include <iostream>
#include <alien.pm/tokenwizard/CommandHandlers/GenTokenCommandHandler.h>
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

UnorderedTokenMap<TOKEN_LENGTH, 5> tokenMap;
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
    cout << sizeof(boost::once_flag) << endl;
    auto ptr = cg.try_set(new C());
    {
        auto ptr_get1 = cg.try_get();
        if(ptr_get1)
            cg.unsafe_decrease_counter();
        ptr_get1 = nullptr;
        auto ptr_get2 = cg.try_get();
        if(ptr_get2)
            cg.unsafe_decrease_counter();
    }
    tokenDestroyedPacket.serialize();
    tokenDoesNotExistPacket.serialize();

    handlerSelector.assignHandler((char)ClientCommand::getToken, new GetTokenCommandHandler());
    handlerSelector.assignHandler((char)ClientCommand::genToken, new GenTokenCommandHandler());

    string data = "123456789";
    auto res = tokenMap.genToken(data.c_str(), data.size());
    cout << res->token << endl;

    try {
        if (argc != 2) {
            std::cerr << "Port is non set\n";
            return 1;
        }
        TokenServer tokenServer(primary_io_service, static_cast<short>(std::atoi(argv[1])), 3);
        primary_io_service.run();
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}