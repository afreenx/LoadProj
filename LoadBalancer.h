#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "Request.h"
#include "Webserver.h"
#include <queue>

/**
 * @brief The LoadBalancer class manages the web servers and the request queue.
 */
class LoadBalancer {
public:
    /**
     * @brief Constructs a new LoadBalancer object.
     */
    LoadBalancer();

    /**
     * @brief Retrieves the current time of the load balancer.
     *
     * @return The current time of the load balancer.
     */
    int getTime();

    /**
     * @brief Updates the time of the load balancer by incrementing it by 1.
     */
    void updateTime();

    /**
     * @brief Retrieves the size of the request queue.
     *
     * @return The size of the request queue.
     */
    int sizeQueue();

    /**
     * @brief Checks if the request queue is empty.
     *
     * @return True if the request queue is empty, false otherwise.
     */
    bool emptyQueueCheck();

    /**
     * @brief Pops the next request from the request queue.
     *
     * @return A pointer to the next request in the queue, or nullptr if the queue is empty.
     */
    Request* popRequest();

    /**
     * @brief Pushes a request into the request queue.
     *
     * @param req A pointer to the request to be pushed into the queue.
     */
    void pushRequest(Request* req);

private:
    int time; /**< The current time of the load balancer. */
    std::queue<Request*> reqQueue; /**< The queue of requests to be processed by the load balancer. */
};

#endif
