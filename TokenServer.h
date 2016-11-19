#ifndef TOKENWIZARD_TOKENSERVER_H
#define TOKENWIZARD_TOKENSERVER_H

#include <thread>
#include "BaseHeader.h"
#include "TcpSession.h"
#include "Worker.h"

using namespace boost::asio;

class TokenServer {
    void acceptLoop();
    io_service& mIoService;
    tcp::acceptor mAcceptor;
    tcp::socket mCurrSocket;
    vector<Worker*> workers;
    size_t concurrencyLevel;
    size_t roundRobinIterator = 0;

    Worker* getNextWorker() {
        ++roundRobinIterator;
        if(roundRobinIterator == concurrencyLevel)
            roundRobinIterator = 0;
        return  workers[roundRobinIterator];
    }

    public:
    TokenServer(boost::asio::io_service& _io_service, short port, size_t cl)
                : mAcceptor(_io_service, tcp::endpoint(tcp::v4(), port)),
                  mIoService(_io_service), concurrencyLevel(cl), mCurrSocket(_io_service)
        {
            for(int i = 0; i < concurrencyLevel; ++i) {
                workers.push_back(new Worker());
            }
            acceptLoop();
        }
};


#endif //TOKENWIZARD_TOKENSERVER_H