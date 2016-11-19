#include <thread>
#include "TcpSession.h"

TcpSession::TcpSession(tcp::socket socket, Worker* myWorker):
        mSocket(std::move(socket)), myWorker(myWorker)
{
    writeOffset = mData;
    readOffset = mData;
    cout << "Session has been created!" << endl;
}

TcpSession::~TcpSession() {
    cout << "Session has been destroyed!" << endl;
}

void TcpSession::BeginCommunication() {
    auto self = shared_from_this();
    myWorker->workerService->post([this, self]()
                    {
                        read_loop();
                    }
    );
}
