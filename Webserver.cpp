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
  
}

void WebServer::blockIPRange(const std::string& ipRange) {
    
}
