#ifndef TOKENWIZARD_TOKENSERVER_H
#define TOKENWIZARD_TOKENSERVER_H

#include "BaseHeader.h"
#include "TcpSession.h"


class TokenServer {
    void doAccept();
    boost::asio::io_service& mIoService;
    tcp::acceptor mAcceptor;
    tcp::socket mSocket;
    public:
    TokenServer(boost::asio::io_service& io_service, short port)
                : mAcceptor(io_service, tcp::endpoint(tcp::v4(), port)),
                  mSocket(io_service), mIoService(io_service)
        {
            doAccept();
        }
};


#endif //TOKENWIZARD_TOKENSERVER_H