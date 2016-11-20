#ifndef TOKENWIZARD_SESSION_H
#define TOKENWIZARD_SESSION_H

#include "BaseHeader.h"
#include "HandlerSelector.h"
#include "Worker.h"


extern HandlerSelector handlerSelector;

class TcpSession: public std::enable_shared_from_this<TcpSession> {
    tcp::socket mSocket;
    enum {
        maxLength = 65536
    };
    char mData[maxLength];
    void handlePacket(char *bytes, size_t size);
    char *writeOffset;
    char *readOffset;
    size_t currSize = 0;
    bool sendDaemonStarted = false;
    boost::posix_time::milliseconds mSendInterval;
    boost::asio::deadline_timer* timer;

    void sendDaemonTick() {
        sendDaemonStarted = false;
        if(currentBuffer->currSize)
            replacePBuff();
        std::cout << "sd tick" << std::endl;
    }

    void tryStartDaemon() {
        if(!sendDaemonStarted) {
            sendDaemonStarted = true;
            timer->expires_from_now(boost::posix_time::seconds(5));
            //timer->async_wait(std::bind(&TcpSession::sendDaemonTick, this));
        }
    }

    void readHandler(size_t written);
    void read_loop();
public:
    Worker* myWorker;
    PBuff* currentBuffer;
    void sendCurrPBuff();
    void replacePBuff();
    Packet beginPacket(size_t size);
    void endPacket(Packet& p);
    void writeStaticPacket(StaticPacket& p);
    PBuff* getPacketBuffer(size_t maxSize);
    TcpSession(tcp::socket socket, Worker* myWorker);
    void BeginCommunication();
    ~TcpSession();
};

#endif //TOKENWIZARD_SESSION_H
