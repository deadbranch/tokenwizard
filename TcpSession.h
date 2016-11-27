#ifndef TOKENWIZARD_SESSION_H
#define TOKENWIZARD_SESSION_H

#include "BaseHeader.h"
#include "HandlerSelector.h"
#include "Worker.h"


extern HandlerSelector handlerSelector;

class TcpSession: public std::enable_shared_from_this<TcpSession> {
    tcp::socket mSocket;
    enum {
        bufferLength = 65536
    };
    char mData[bufferLength];
    void handlePacket(char *bytes, size_t size);
    char *writeOffset;
    char *readOffset;
    size_t currSize = 0;
    bool sendDaemonStarted = false;
    boost::posix_time::milliseconds mSendInterval;
    boost::asio::deadline_timer* timer;
    shared_ptr<TcpSession> sendDaemonProtector = nullptr;
    void sendDaemonTick();
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
    void startSendDaemon();
    void BeginCommunication();
    ~TcpSession();
};

#endif //TOKENWIZARD_SESSION_H
