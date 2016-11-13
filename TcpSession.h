//
// Created by origin on 29.10.16.
//

#ifndef TOKENWIZARD_SESSION_H
#define TOKENWIZARD_SESSION_H

#include "BaseHeader.h"
#include "serialization/Packet.h"

class TcpSession: public std::enable_shared_from_this<TcpSession> {
    boost::asio::io_service& mIoService;
    tcp::socket mSocket;
    char mData[1024];
    int maxLength = 1024;
    void do_read()
    {
        auto self(shared_from_this());
        mSocket.async_read_some(boost::asio::buffer(mData, maxLength),
                                [this, self](boost::system::error_code ec, std::size_t length)
                                {
                                    if (!ec)
                                    {
                                        do_write(length);
                                    }
                                });
    }

    void do_write(std::size_t length)
    {
        auto self(shared_from_this());
        boost::asio::async_write(mSocket, boost::asio::buffer(mData, length),
                                 [this, self](boost::system::error_code ec, std::size_t )
                                 {
                                     if (!ec)
                                     {
                                         do_read();
                                     }
                                 });
    }

public:
    template <class T>
    void SendPacket(Packet* packet, T&& shared_ptr);
    TcpSession(tcp::socket socket, boost::asio::io_service& _io_service);
    void BeginCommunication();
    ~TcpSession();
};

#endif //TOKENWIZARD_SESSION_H
