#include "TokenServer.h"

void TokenServer::acceptLoop() {
    auto pSelectedWorker = getNextWorker();
    mCurrSocket = tcp::socket(*pSelectedWorker->workerService);
    mAcceptor.async_accept(mCurrSocket,
                           [this, pSelectedWorker](boost::system::error_code ec)
                           {
                               if (!ec)
                               {
                                   std::make_shared<TcpSession>(std::move(mCurrSocket), pSelectedWorker)->BeginCommunication();
                               }
                               acceptLoop();
                           });
}