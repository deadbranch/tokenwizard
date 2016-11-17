#include "TcpSession.h"

TcpSession::TcpSession(tcp::socket socket, boost::asio::io_service &_io_service):
        mSocket(std::move(socket)), mIoService(_io_service)
{
    writeOffset = mData;
    readOffset = mData;
    cout << "Session has been created!" << endl;
}

TcpSession::~TcpSession() {
    cout << "Session has been destroyed!" << endl;
}

void TcpSession::BeginCommunication() {
    read_loop();
}
