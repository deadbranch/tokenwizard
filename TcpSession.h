//
// Created by origin on 29.10.16.
//

#ifndef TOKENWIZARD_SESSION_H
#define TOKENWIZARD_SESSION_H

#include "BaseHeader.h"
#include "serialization/Packet.h"
#include "HandlerSelector.h"
#include "Worker.h"

extern HandlerSelector handlerSelector;

class TcpSession: public std::enable_shared_from_this<TcpSession> {
    Worker* myWorker;
    tcp::socket mSocket;
    enum {
        maxLength = 65536
    };
    char mData[maxLength];

    void handlePacket(char *bytes, size_t size) {
        auto handlerPtr = handlerSelector.getHandler(*bytes);
        assert(handlerPtr);
        if (handlerPtr)
            handlerPtr->Handle(bytes, size, *this);
    }

    char *writeOffset;
    char *readOffset;
    size_t currSize = 0;

    void readHandler(size_t written) {
        currSize += written;
        writeOffset += written;
        while (true) {
            uint32_t packetSize = fixEndianness(*reinterpret_cast<uint32_t *>(readOffset));
            if ((packetSize + 4) <= currSize) {
                handlePacket(readOffset + 4, packetSize);
                readOffset += 4 + packetSize;
                currSize -= 4 + packetSize;
            } else
                break;
        }
        if (currSize) {
            memmove(mData, readOffset, currSize);
        }
        readOffset = mData;
        writeOffset = readOffset + currSize;
    }

    void read_loop() {
        auto self(shared_from_this());
        mSocket.async_read_some(boost::asio::buffer(writeOffset, maxLength - currSize),
                                [this, self](boost::system::error_code ec, std::size_t length) {
                                    if (!ec) {
                                        readHandler(length);
                                        read_loop();
                                    }
                                });
    }


public:
    template<class T>
    void SendPacket(Packet *packet, T &&smart_pointer) {
        auto self = shared_from_this();
        boost::asio::async_write(mSocket, boost::asio::buffer(packet -> data(), packet->size()),
                                 [self, packet, smart_pointer](boost::system::error_code ec, std::size_t l)
                                 {
                                     if (!ec) {
                                         //cout << "Sent!" << endl;
                                     }
                                 });
    }
    void SendPacket(Packet *packet) {
        auto self = shared_from_this();
        boost::asio::async_write(mSocket, boost::asio::buffer(packet -> data(), packet->size()),
                                 [self, packet](boost::system::error_code ec, std::size_t l)
                                 {
                                     if (!ec) {
                                         cout << "Sent!" << endl;
                                     }
                                 });
    }
    TcpSession(tcp::socket socket, Worker* myWorker);
    void BeginCommunication();
    ~TcpSession();
};

#endif //TOKENWIZARD_SESSION_H
