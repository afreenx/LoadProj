#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "Request.h"
#include "Webserver.h"
#include <queue>

class LoadBalancer {
public:
    LoadBalancer();
    int getTime();
    void updateTime();
    int sizeQueue();
    bool emptyQueueCheck();
    Request* popRequest();
    void pushRequest(Request* req);

private:
    int time;
    std::queue<Request*> reqQueue;
};

#endif
