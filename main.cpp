#include "LoadBalancer.h"
#include "Webserver.h"

#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>

void myNewLogFile(std::ofstream& ofs, int numServers, int runTime, const std::string& ipRange) {
    std::string fileName = "LoadBalancerLog.txt";
    ofs.open(fileName, std::ios::out | std::ios::trunc);

    ofs << "Log of " << numServers << " Computing nodes running for " << runTime << " clock cycles" << std::endl;
    ofs << "Computing web server nodes for blocked IP range: " << ipRange << std::endl;
    std::cout << "Blocked IP range: " << ipRange << std::endl;
}

void newWebserver(std::vector<WebServer*>& webservers, int numServers, const std::string& ipRange) {
    for (int i = 0; i < numServers; i++) {
        WebServer* webserver = new WebServer(i + 1);
        webserver->blockIPRange(ipRange);
        webservers[i] = webserver;
    }
}

void newStartRequest(LoadBalancer* loadBalancer, int numServers) {
    srand(time(0));
    for (int i = 0; i < (numServers * 2); i++) {
        Request* newReq = new Request();
        newReq->processingTime = rand() % 1000;
        loadBalancer->pushRequest(newReq);
    }
}

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
    ofs << std::endl << std:: endl << "Ending Queue Size: " << loadBalancer->sizeQueue() << std::endl;
}


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
