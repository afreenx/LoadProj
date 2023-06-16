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
    std::cout << "Computing web server nodes for blocked IP range: " << ipRange << std::endl;
}

void newWebserver(std::vector<WebServer*>& webservers, int numServers, const std::string& ipRange) {
    for (int i = 0; i < numServers; i++) {
        WebServer* webserver = new WebServer(i + 1);
        webserver->blockIPRange(ipRange);
        webservers[i] = webserver;
    }
}

void newStartRequest(LoadBalancer* loadBalancer, int numServers) {
   
}

void processRequests(LoadBalancer* loadBalancer, std::vector<WebServer*>& webservers, std::ofstream& ofs, int runTime) {
   
}

int main() {
    srand(time(0));

    int numServers = 0;
    int runTime = 0;
    int requestsToGenerate = 0;

    std::cout << "Enter number of Computing nodes: ";
    std::cin >> numServers;

    std::cout << "Enter time to run the load balancer: ";
    std::cin >> runTime;

    std::string ipRange;
    std::cout << "Enter IP range to block for all servers: ";
    std::cin >> ipRange;

    std::ofstream ofs;
   
}
