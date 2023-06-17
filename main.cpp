#include "LoadBalancer.h"
#include "Webserver.h"

#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>
/**
 * @brief Creates a new log file and writes information about the load balancer setup.
 *
 * This function creates a new log file named "LoadBalancerLog.txt" and writes information about the load balancer setup
 * to the file. The information includes the number of computing nodes, the runtime, and the blocked IP range.
 *
 * @param ofs The output file stream object to write the log information.
 * @param numServers The number of computing nodes in the load balancer.
 * @param runTime The runtime of the load balancer in clock cycles.
 * @param ipRange The blocked IP range for the load balancer.
 */
void myNewLogFile(std::ofstream& ofs, int numServers, int runTime, const std::string& ipRange) {
    std::string fileName = "LoadBalancerLog.txt";
    ofs.open(fileName, std::ios::out | std::ios::trunc);

    ofs << "Log of " << numServers << " Computing nodes running for " << runTime << " clock cycles" << std::endl;
    ofs << "Computing web server nodes for blocked IP range: " << ipRange << std::endl;
    std::cout << "Blocked IP range: " << ipRange << std::endl;
}

/**
 * @brief Creates new web server objects and adds them to a vector.
 *
 * This function creates a specified number of web server objects and adds them to the provided vector. Each web server
 * object is assigned a unique identifier starting from 1. The IP range specified is blocked for each web server.
 *
 * @param webservers A vector to store the created web server objects.
 * @param numServers The number of web server objects to create.
 * @param ipRange The IP range to block for each web server.
 */
void newWebserver(std::vector<WebServer*>& webservers, int numServers, const std::string& ipRange) {
    for (int i = 0; i < numServers; i++) {
        WebServer* webserver = new WebServer(i + 1);
        webserver->blockIPRange(ipRange);
        webservers[i] = webserver;
    }
}

/**
 * @brief Generates and pushes new requests to the load balancer.
 *
 * This function generates a specified number of new request objects and pushes them to the load balancer. Each request
 * object has a randomly assigned processing time between 0 and 999 (inclusive).
 *
 * @param loadBalancer A pointer to the load balancer object.
 * @param numServers The number of servers managed by the load balancer.
 */
void newStartRequest(LoadBalancer* loadBalancer, int numServers) {
    srand(time(0));
    for (int i = 0; i < (numServers * 2); i++) {
        Request* newReq = new Request();
        newReq->processingTime = rand() % 1000;
        loadBalancer->pushRequest(newReq);
    }
}

/**
 * @brief Processes requests in the load balancer.
 *
 * This function processes requests in the load balancer until the specified runtime is reached. It iterates through each
 * web server in the provided vector and checks if a request is completed. If a request is completed, it updates the range
 * of processing times and writes the completion information to the output file stream and standard output. After processing
 * each web server, it generates a new request and pushes it to the load balancer. If the queue size exceeds 15, an additional
 * request is added to the queue. The function also updates the time in the load balancer after each iteration.
 *
 * @param loadBalancer A pointer to the load balancer object.
 * @param webservers A vector containing web server objects.
 * @param ofs The output file stream object to write the completion information.
 * @param runTime The runtime of the load balancer.
 */
void processRequests(LoadBalancer* loadBalancer, std::vector<WebServer*>& webservers, std::ofstream& ofs, int runTime) {
    int rangeMin = webservers[0]->getRequest()->processingTime;
    int rangeMax = webservers[0]->getRequest()->processingTime;

    while (loadBalancer->getTime() < runTime) {
        for (std::vector<WebServer*>::size_type i = 0; i < webservers.size(); i++) {
            int currentTime = loadBalancer->getTime();
            WebServer* webserver = webservers[i];

            if (webserver->getRequest() != nullptr && webserver->reqDone(currentTime)) {
                Request* processedRequest = webserver->getRequest();

                if (processedRequest->processingTime < rangeMin) {
                    rangeMin = processedRequest->processingTime;
                }
                else if (processedRequest->processingTime > rangeMax) {
                    rangeMax = processedRequest->processingTime;
                }

                ofs << "Computing web server node " << webserver->getServerName() << " completed running request from " + processedRequest->inputIP + " to " +
                    processedRequest->outputIP + " at time " << currentTime << std::endl;
                std::cout << " Computing web server node " << webserver->getServerName() << " completed running request from " + processedRequest->inputIP + " to " +
                    processedRequest->outputIP + " at time " << currentTime << std::endl;

                delete processedRequest;
                webserver->processRequest(loadBalancer->popRequest(), currentTime);
            }
        }

        Request* newReq = new Request();
        newReq->processingTime = rand() % 1000;
        loadBalancer->pushRequest(newReq);

        if (loadBalancer->sizeQueue() > 15) {
            Request* newReq = new Request();
            newReq->processingTime = rand() % 1000;
            loadBalancer->pushRequest(newReq);
        }

        loadBalancer->updateTime();
    }

    ofs << std::endl << "Min Task Time = " << rangeMin << ", Max Task Time =  " << rangeMax << std::endl;
    ofs << "Range is therefore " << rangeMin << " to " << rangeMax << std::endl;
    ofs << std::endl << std::endl << "Ending Queue Size: " << loadBalancer->sizeQueue() << std::endl;
}



/**
 * @brief The entry point of the program.
 *
 * This function is the entry point of the program. It initializes the random number generator, prompts the user to enter
 * the number of computing nodes, the runtime of the load balancer, and the IP range to block for all servers. It creates
 * a new log file using the provided information and initializes a vector to hold the web server objects. It creates the
 * web server objects and assigns the blocked IP range to each server. It also creates a new load balancer object and
 * generates initial requests. It processes the requests and writes the completion information to the log file. Finally,
 * it performs cleanup by deleting the load balancer object, web server objects, and closing the log file.
 *
 * @return An integer indicating the exit status of the program.
 */
int main() {
    srand(time(0));

    int numServers = 0;
    int runTime = 0;
    int startsizeQ = 0;

    std::cout << "Enter number of Computing node: ";
    std::cin >> numServers;

    std::cout << "Enter time to run the load balancer: ";
    std::cin >> runTime;

    std::string ipRange;
    std::cout << "Enter IP range to block for all servers: ";
    std::cin >> ipRange;

    std::ofstream ofs;
    myNewLogFile(ofs, numServers, runTime, ipRange);

    std::vector<WebServer*> webservers(numServers, nullptr); // vector that holds webservers
    newWebserver(webservers, numServers, ipRange);

    LoadBalancer* loadBalancer = new LoadBalancer();

    newStartRequest(loadBalancer, numServers);
    startsizeQ = loadBalancer->sizeQueue();

    for (int i = 0; i < numServers; i++) {
        WebServer* webserver = webservers[i];
        webserver->processRequest(loadBalancer->popRequest(), loadBalancer->getTime());
    }

    processRequests(loadBalancer, webservers, ofs, runTime);
    ofs << "Starting Queue size: " << startsizeQ << std::endl << std::endl;

    delete loadBalancer;

    for (WebServer* webserver : webservers) {
        delete webserver;
    }

    ofs.close();

    return 0;
}
