#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"
#include <string>
#include <vector>

class WebServer {
private:
    int serverName;
    int reqStart;
    Request* request;
    std::vector<std::string> blockedIPranges;

public:
    WebServer(int server_name);
    Request* getRequest();
    int getServerName();
    bool reqDone(int currTime);
    void processRequest(Request* req, int currTime);
    void blockIPRange(const std::string& ipRange);
    bool isIPAddressInRange(const std::string& ipAddress, const std::string& ipRange);
};

#endif
