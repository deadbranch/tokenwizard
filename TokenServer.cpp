#include "TokenServer.h"

void TokenServer::doAccept() {
    mAcceptor.async_accept(mSocket,
                           [this](boost::system::error_code ec)
                           {
                               if (!ec)
                               {
                                   std::make_shared<TcpSession>(std::move(mSocket), mIoService)->BeginCommunication();
                               }
                               doAccept();
                           });
}