#include "TcpSession.h"

TcpSession::TcpSession(tcp::socket socket, boost::asio::io_service &_io_service):
        mSocket(std::move(socket)), mIoService(_io_service)
{
    cout << "Session has been created!" << endl;
}

TcpSession::~TcpSession() {
    cout << "Session has been destroyed!" << endl;
}

template <class T>
void TcpSession::SendPacket(Packet* packet, T&& shared_ptr){
    auto self = shared_from_this();
    boost::asio::async_write(mSocket, boost::asio::buffer(packet->data(), packet->size()),
                             [self, packet, shared_ptr](boost::system::error_code ec, std::size_t l)
                             {
                                 if(!ec) {
                                     cout << "Sent!" << endl;

                                 }
                             });
}

void TcpSession::BeginCommunication() {
    do_read();
}
