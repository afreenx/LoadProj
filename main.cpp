#include "loadbalancer.h"
#include "webserver.h"

#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>

void myNewlogFile(std::ofstream& ofs, int numServers, int runTime, const std::string& ipRange) {
   
}

void newWebserver(std::vector<WebServer*>& webservers, int numServers, const std::string& ipRange) {
  
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
