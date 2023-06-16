#ifndef REQUEST_H
#define REQUEST_H

#include <cstdlib>
#include <string>


struct Request {
    std::string inputIP = std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." +
        std::to_string(rand() % 256) + "." + std::to_string(rand() % 256); 

    std::string outputIP = std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." +
        std::to_string(rand() % 256) + "." + std::to_string(rand() % 256); 

    int processingTime; 
};

#endif