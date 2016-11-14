//
// Created by origin on 29.10.16.
//

#ifndef TOKENWIZARD_SESSION_H
#define TOKENWIZARD_SESSION_H

#include "BaseHeader.h"
#include "serialization/Packet.h"
#include "HandlerSelector.h"

extern HandlerSelector handlerSelector;

class TcpSession: public std::enable_shared_from_this<TcpSession> {
    boost::asio::io_service& mIoService;
    tcp::socket mSocket;
    enum {
        maxLength = 65536
    };
    char mData[maxLength];

    void HandleCmd(char* bytes, size_t size) {
        auto handlerPtr = handlerSelector.getParser(*bytes);
        assert(handlerPtr);
        if(handlerPtr)
            handlerPtr->Handle(bytes, size, *this);
    }

    char* writeOffset;
    char* readOffset;

    size_t currSize = 0;

    void HandleRead(size_t written) {
        currSize += written;
        writeOffset += written;
        while(true) {
            uint32_t packetSize = fixEndianness(*reinterpret_cast<uint32_t *>(readOffset));
            if ((packetSize + 4) <= currSize) {
                HandleCmd(readOffset + 4, packetSize);
                readOffset += 4 + packetSize;
                currSize -= 4 + packetSize;
            }
            else
                break;
        }
        if(currSize) {
            memmove(mData, readOffset, currSize);
        }
        readOffset = mData;
        writeOffset = readOffset+currSize;
    }

    void do_read()
    {
        auto self(shared_from_this());
        mSocket.async_read_some(boost::asio::buffer(writeOffset, maxLength - currSize),
                                [this, self](boost::system::error_code ec, std::size_t length)
                                {
                                    if (!ec)
                                    {
                                        HandleRead(length);
                                        do_read();
                                    }
                                });
    }


public:
    template <class T>
    void SendPacket(Packet* packet, T&& smart_pointer);
    TcpSession(tcp::socket socket, boost::asio::io_service& _io_service);
    void BeginCommunication();
    ~TcpSession();
};

/*
 *
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
 * */
#endif //TOKENWIZARD_SESSION_H
