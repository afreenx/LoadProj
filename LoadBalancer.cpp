#include "LoadBalancer.h"
//loadbalancer class that manages the webservers and the request queue

/**
 * @brief Constructs a new LoadBalancer object.
 *
 * The LoadBalancer class manages the web servers and the request queue.
 */
LoadBalancer::LoadBalancer() {
    this->time = 0; /**< The current time of the load balancer. */
}

/**
 * @brief Retrieves the current time of the load balancer.
 *
 * @return The current time of the load balancer.
 */
int LoadBalancer::getTime() {
    return this->time;
}

/**
 * @brief Updates the time of the load balancer by incrementing it by 1.
 */
void LoadBalancer::updateTime() {
    this->time++;
}

/**
 * @brief Checks if the request queue is empty.
 *
 * @return True if the request queue is empty, false otherwise.
 */
bool LoadBalancer::emptyQueueCheck() {
    return this->reqQueue.empty();
}

/**
 * @brief Retrieves the size of the request queue.
 *
 * @return The size of the request queue.
 */
int LoadBalancer::sizeQueue() {
    return this->reqQueue.size();
}

/**
 * @brief Pops the next request from the request queue.
 *
 * @return A pointer to the next request in the queue, or nullptr if the queue is empty.
 */
Request* LoadBalancer::popRequest() {
    if (this->emptyQueueCheck()) {
        return nullptr;
    }
    Request* nextReq = this->reqQueue.front();
    this->reqQueue.pop();

    return nextReq;
}

/**
 * @brief Pushes a request into the request queue.
 *
 * @param req A pointer to the request to be pushed into the queue.
 */
void LoadBalancer::pushRequest(Request* req) {
    this->reqQueue.push(req);
}
