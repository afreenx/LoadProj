#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"
#include <string>
#include <vector>

/**
 * @brief The WebServer class represents a web server node that can process requests.
 */
class WebServer {
private:
    int serverName; /**< The name of the web server. */
    int reqStart; /**< The start time of the current request being processed. */
    Request* request; /**< The current request assigned to the web server. */
    std::vector<std::string> blockedIPRanges; /**< List of blocked IP ranges on the web server. */

public:
    /**
     * @brief Constructs a new WebServer object with the given server name.
     *
     * @param server_name The name of the server.
     */
    WebServer(int server_name);

    /**
     * @brief Retrieves the current request assigned to the web server.
     *
     * @return A pointer to the current request assigned to the web server.
     */
    Request* getRequest();

    /**
     * @brief Retrieves the name of the web server.
     *
     * @return The name of the web server.
     */
    int getServerName();

    /**
     * @brief Checks if the current request assigned to the web server is done processing.
     *
     * @param currTime The current time.
     * @return True if the request is done processing, false otherwise.
     */
    bool reqDone(int currTime);

    /**
     * @brief Assigns a new request to the web server and sets the start time.
     *
     * @param req The request to be assigned.
     * @param currTime The current time.
     */
    void processRequest(Request* req, int currTime);

    /**
     * @brief Blocks an IP range on the web server.
     *
     * @param ipRange The IP range to block in the form "network_address/subnet_mask".
     */
    void blockIPRange(const std::string& ipRange);

    /**
     * @brief Checks if an IP address is within the specified IP range.
     *
     * @param ipAddress The IP address to check.
     * @param ipRange The IP range in the form "network_address/subnet_mask".
     * @return True if the IP address is within the range, false otherwise.
     */
    bool isIPAddressInRange(const std::string& ipAddress, const std::string& ipRange);
};

#endif
