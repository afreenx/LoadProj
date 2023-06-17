/**
 * @file mainpage.h
 *
 * @brief Load Balancer Project Workflow
 */

/**
 * @mainpage Load Balancer Project Workflow
 *
 * @section Introduction Introduction
 *
 * This documentation provides an overview of the workflow for a Load Balancer project.
 * It outlines the steps involved in initializing the load balancer, generating initial requests,
 * processing requests, and finalizing the project.
 *
 * @section Workflow Workflow
 *
 * The workflow of the Load Balancer project can be divided into the following phases:
 *
 * - Initialization: Set up the load balancer and web servers.
 * - Generate Initial Requests: Create an initial queue of requests.
 * - Process Requests: Assign and process requests on the web servers.
 * - Main Loop: Continuously process requests until the runtime duration is reached.
 * - Finalization: Output results and clean up resources.
 *
 * @section Initialization Initialization
 *
 * The initialization phase involves the following steps:
 * - Obtain the number of computing nodes (web servers) from the user.
 * - Obtain the runtime duration for the load balancer from the user.
 * - Obtain the IP range to block for all servers from the user.
 * - Create a log file to record the load balancer's activity.
 * - Create web servers and block the IP range for each server.
 *
 * @section GenerateRequests Generate Initial Requests
 *
 * The generate requests phase involves the following steps:
 * - Generate a starting queue of requests with random processing times.
 *
 * @section ProcessRequests Processing Requests
 *
 * The request processing phase involves the following steps:
 * - Assign requests from the load balancer's queue to each web server.
 * - Process the assigned requests and record the completion time.
 * - Generate new requests based on certain conditions.
 *
 * @section MainLoop Main Loop
 *
 * The main loop phase involves the following steps:
 * - While the current time of the LoadBalancer is less than the runtime duration:
 *   - Iterate over each WebServer:
 *     - Check if the current request in the WebServer has finished processing:
 *       - If yes, log the completion and process a new request from the LoadBalancer:
 *         - Generate a random request.
 *         - Push it into the LoadBalancer's request queue using the `pushRequest` method.
 *         - If the queue size exceeds a threshold, generate an additional random request.
 *   - Update the current time of the LoadBalancer using the `updateTime` method.
 *
 * @section Finalization Finalization
 *
 * The finalization phase involves the following steps:
 * - Output the minimum and maximum task times. This is for the range. Do this in the Log File Output.
 * - Output the final queue size of the load balancer as well as the start queue size. This is in the Log File Output.
 * - Clean up memory and resources.
 */

#pragma once