#include "LoadBalancer.h"
//loadbalancer class that manages the webservers and the request queue

LoadBalancer::LoadBalancer() {
    //my constructor with the time
    this->time = 0;
}
int LoadBalancer::getTime() {
    return this->time;
}

void LoadBalancer::updateTime() {
    this->time++;
}

bool LoadBalancer::emptyQueueCheck() {
    return this->reqQueue.empty();
}

int LoadBalancer::sizeQueue() {
    return this->reqQueue.size();
}

Request* LoadBalancer::popRequest() {
    if (this->emptyQueueCheck()) {
        return nullptr;
    }
    Request* nextReq = this->reqQueue.front();
    this->reqQueue.pop();

    return nextReq;
}

void LoadBalancer::pushRequest(Request* req) {
    this->reqQueue.push(req);
}

