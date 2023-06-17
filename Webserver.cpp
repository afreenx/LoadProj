#include "webserver.h"
#include <sstream>
#include <iostream>

WebServer::WebServer(int serverName) {
    this->serverName = serverName;
    this->reqStart = 0;
}

Request* WebServer::getRequest() {
    return this->request;
}

int WebServer::getServerName() {
    return this->serverName;
}

bool WebServer::reqDone(int currTime) {
    return ((currTime >= (reqStart + this->request->processingTime)));
}

void WebServer::processRequest(Request* req, int currTime) {
    this->request = req;
    this->reqStart = currTime;
}

bool WebServer::isIPAddressInRange(const std::string& ipAddress, const std::string& ipRange) {
    std::istringstream rangeStream(ipRange);
    std::string networkAddressStr;
    std::getline(rangeStream, networkAddressStr, '/');
    std::string subnetMaskStr;
    std::getline(rangeStream, subnetMaskStr);

    unsigned long networkAddress = 0;
    unsigned long subnetMask = 0;

    std::istringstream networkAddressStream(networkAddressStr);
    std::string octet;
    for (int i = 0; i < 4; i++) {
        std::getline(networkAddressStream, octet, '.');
        networkAddress = (networkAddress << 8) + std::stoi(octet);
    }

    int subnetBits = std::stoi(subnetMaskStr);
    for (int i = 0; i < subnetBits; i++) {
        subnetMask = (subnetMask << 1) + 1;
    }
    subnetMask = subnetMask << (32 - subnetBits);

    unsigned long givenAddress = 0;
    std::istringstream givenAddressStream(ipAddress);
    for (int i = 0; i < 4; i++) {
        std::getline(givenAddressStream, octet, '.');
        givenAddress = (givenAddress << 8) + std::stoi(octet);
    }

    return ((givenAddress & subnetMask) == networkAddress);
}


void WebServer::blockIPRange(const std::string& ipRange) {
    blockedIPRanges.push_back(ipRange);
}
