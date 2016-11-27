#include <thread>
#include "TcpSession.h"

TcpSession::TcpSession(tcp::socket socket, Worker* myWorker):
        mSocket(std::move(socket)), myWorker(myWorker), mSendInterval(SEND_INTERVAL)
{
    currentBuffer = new PBuff();
    timer = new deadline_timer(*myWorker->workerService, mSendInterval);
    writeOffset = mData;
    readOffset = mData;
    cout << "Session has been created!" << endl;
}



void TcpSession::BeginCommunication() {
    auto self = shared_from_this();
    myWorker->workerService->post([this, self]()
                    {
                        read_loop();
                    }
    );
}

void TcpSession::handlePacket(char *bytes, size_t size) {
    auto handlerPtr = handlerSelector.getHandler(*bytes);
    assert(handlerPtr);
    if (handlerPtr)
        handlerPtr->Handle(bytes, size, *this);
}

void TcpSession::readHandler(size_t written) {
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

void TcpSession::read_loop() {
    auto self(shared_from_this());
    mSocket.async_read_some(boost::asio::buffer(writeOffset, bufferLength - currSize),
                            [this, self](boost::system::error_code ec, std::size_t length) {
                                if (!ec) {
                                    readHandler(length);
                                    read_loop();
                                }
                                else {
                                    int a = 2;
                                }
                            });
}

void TcpSession::sendCurrPBuff() {
    auto self = shared_from_this();
    PBuff* pbuff = currentBuffer;
    boost::asio::async_write(mSocket, boost::asio::buffer(pbuff->getBuff(), pbuff->currSize),
                             [self, pbuff](boost::system::error_code ec, std::size_t l)
                             {
                                 if (!ec) {
                                     cout << "Sent! " << pbuff->currSize << endl;
                                 }
                                 delete pbuff;
                             });
}

void TcpSession::replacePBuff() {
    sendCurrPBuff();
    currentBuffer = new PBuff();
}

void TcpSession::writeStaticPacket(StaticPacket &p) {
    if(currentBuffer->bytesLeft() < p.size())
        replacePBuff();
    currentBuffer->writeStaticPacket(p);
    startSendDaemon();
}

PBuff* TcpSession::getPacketBuffer(size_t maxSize) {
    if(currentBuffer->bytesLeft() < maxSize)
        replacePBuff();
    return currentBuffer;
}

void TcpSession::sendDaemonTick() {
    std::cout << "sd tick" << std::endl;
    if(currentBuffer->currSize)
        replacePBuff();
    sendDaemonProtector = nullptr;
    sendDaemonStarted = false;
}

void TcpSession::startSendDaemon() {
    if(!sendDaemonStarted) {
        sendDaemonProtector = shared_from_this();
        sendDaemonStarted = true;
        timer->expires_from_now(boost::posix_time::milliseconds(SEND_INTERVAL));
        timer->async_wait(std::bind(&TcpSession::sendDaemonTick, this));
    }
}

TcpSession::~TcpSession() {
    cout << "Session has been destroyed!" << endl;
}