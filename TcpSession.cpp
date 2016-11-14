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

template <class T>
void TcpSession::SendPacket(Packet* packet, T&& smart_pointer){
    auto self = shared_from_this();
    boost::asio::async_write(mSocket, boost::asio::buffer(packet->data(), packet->size()),
                             [self, packet, smart_pointer](boost::system::error_code ec, std::size_t l)
                             {
                                 if(!ec) {
                                     cout << "Sent!" << endl;
                                 }
                             });
}

void TcpSession::BeginCommunication() {
    do_read();
}
