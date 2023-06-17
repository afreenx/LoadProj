#include "webserver.h"
#include <sstream>
#include <iostream>

/**
 * @brief Constructs a new WebServer object with the given server name.
 *
 * @param serverName The name of the server.
 */
WebServer::WebServer(int serverName) {
    this->serverName = serverName;
    this->reqStart = 0;
}

/**
 * @brief Retrieves the current request assigned to the web server.
 *
 * @return A pointer to the current request assigned to the web server.
 */
Request* WebServer::getRequest() {
    return this->request;
}

/**
 * @brief Retrieves the name of the web server.
 *
 * @return The name of the web server.
 */
int WebServer::getServerName() {
    return this->serverName;
}

/**
 * @brief Checks if the current request assigned to the web server is done processing.
 *
 * @param currTime The current time.
 * @return True if the request is done processing, false otherwise.
 */
bool WebServer::reqDone(int currTime) {
    return ((currTime >= (reqStart + this->request->processingTime)));
}

/**
 * @brief Assigns a new request to the web server and sets the start time.
 *
 * @param req The request to be assigned.
 * @param currTime The current time.
 */
void WebServer::processRequest(Request* req, int currTime) {
    this->request = req;
    this->reqStart = currTime;
}

/**
 * @brief Checks if an IP address is within the specified IP range.
 *
 * @param ipAddress The IP address to check.
 * @param ipRange The IP range in the form "network_address/subnet_mask".
 * @return True if the IP address is within the range, false otherwise.
 */
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

/**
 * @brief Blocks an IP range on the web server.
 *
 * @param ipRange The IP range to block in the form "network_address/subnet_mask".
 */
void WebServer::blockIPRange(const std::string& ipRange) {
    blockedIPRanges.push_back(ipRange);
}
