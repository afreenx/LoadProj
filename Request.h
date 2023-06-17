#ifndef REQUEST_H
#define REQUEST_H

#include <cstdlib>
#include <string>


/**
 * @brief Represents a request with input and output IP addresses and processing time.
 *
 * The Request struct represents a request with input and output IP addresses and a processing time. It generates random
 * IP addresses within the range of 0.0.0.0 to 255.255.255.255 for both the input and output IP addresses. The processing
 * time is an integer value.
 */
struct Request {
    std::string inputIP = std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." +
        std::to_string(rand() % 256) + "." + std::to_string(rand() % 256); /**< The input IP address of the request. */

    std::string outputIP = std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." +
        std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);  /**< The output IP address of the request. */

    int processingTime; /**< The processing time for the request. */
};

#endif
