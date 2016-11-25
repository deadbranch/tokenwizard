#ifndef TOKENWIZARD_WORKER_H
#define TOKENWIZARD_WORKER_H

#include <thread>
#include <queue>
#include "BaseHeader.h"
#include "TokenRecord.h"

using namespace boost::asio;

class Worker {
    typedef cg_shared_ptr<TokenRecord<TOKEN_LENGTH>> TokenPtr;
    boost::asio::io_service::work* gcWork;

    boost::posix_time::seconds interval; // 1 second
    boost::asio::deadline_timer* timer;
    time_t currTime;
    void gcTick() {
        /*
        currTime = time(0);
        size_t currSize = removeQueue.size();
        for(size_t i = 0; i < currSize; ++i) {
            auto ptr = removeQueue.front();
            if(ptr->timeToDie < currTime)
                removeQueue.pop();
            else
                break;
        }
        //std::cout << "gcTick" << std::endl;
        timer->expires_at(timer->expires_at() + interval);
        timer->async_wait(std::bind(&Worker::gcTick, this));
        */
    }
public:
    void pushRemoveTask(TokenPtr&& tokenPtr) {
        removeQueue.push(move(tokenPtr));
    }
    queue<TokenPtr> removeQueue;
    io_service* workerService;
    Worker(): interval(1) {
        currTime = time(0);
        workerService = new io_service();
        gcWork = new io_service::work(*workerService);
        timer = new deadline_timer(*workerService, interval);
        timer->async_wait(std::bind(&Worker::gcTick, this));
        thread([this]() {
            workerService->run();
        }).detach();
    }
};


#endif //TOKENWIZARD_WORKER_H
