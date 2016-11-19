#ifndef TOKENWIZARD_WORKER_H
#define TOKENWIZARD_WORKER_H

#include <thread>
#include "BaseHeader.h"
using namespace boost::asio;

class Worker {
    boost::asio::io_service::work* fakeWork;
public:
    io_service* workerService;
    Worker() {
        workerService = new io_service();
        fakeWork = new io_service::work(*workerService);
        thread([this]() {
            workerService->run();
        }).detach();
    }
};


#endif //TOKENWIZARD_WORKER_H
