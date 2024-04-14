#ifndef SERVER_NETWORK_HANDLER_HPP
#define SERVER_NETWORK_HANDLER_HPP

#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <unordered_map>
#include "parser.hpp"

namespace ssd {

#define BUFFER_SIZE 96

/**
 * @class ServerNetworkHandler
 * @brief Handles network communication for server-client interactions.
 *
 * This class is responsible for sending responses to and receiving requests from a client using TCP sockets. It manages the socket lifecycle and data buffers.
 */
    class ServerNetworkHandler {
    public:
        /**
         * @brief Construct a new Server Network Handler object.
         *
         * Initializes the handler with a client socket and allocates a buffer for data transmission.
         * @param socket The socket descriptor associated with a client connection.
         */
        explicit ServerNetworkHandler(int socket);

        // Delete the copy constructor
        ServerNetworkHandler(const ServerNetworkHandler &) = delete;

        // Delete the assignment operator
        ServerNetworkHandler &operator=(const ServerNetworkHandler &) = delete;

        /**
         * @brief Move constructor.
         *
         * Transfers ownership of resources from another instance.
         * @param other R-value reference to another ServerNetworkHandler.
         */
        ServerNetworkHandler(ServerNetworkHandler &&other) noexcept;

        /**
         * @brief Move assignment operator.
         *
         * Transfers ownership of resources from another instance and cleans up existing resources.
         * @param other R-value reference to another ServerNetworkHandler.
         * @return ServerNetworkHandler& Reference to this instance.
         */
        ServerNetworkHandler &operator=(ServerNetworkHandler &&other) noexcept;

        /**
         * @brief Destroy the Server Network Handler object.
         *
         * Cleans up allocated resources and closes the client socket if it's still open.
         */
        ~ServerNetworkHandler();

        /**
         * @brief Sends a response to the client.
         *
         * Serializes the response data into a string and sends it through the socket.
         * @param keyValuePairs The response data as a key-value map.
         * @exception std::runtime_error Thrown if the send operation fails.
         */
        void sendResponse(const std::unordered_map<std::string, std::string> &keyValuePairs) const;

        /**
         * @brief Receives a request from the client.
         *
         * Reads data from the socket until a complete request is received and deserializes it into a key-value map.
         * @return std::unordered_map<std::string, std::string> The received request data.
         * @exception std::runtime_error Thrown if there's an error during receive.
         */
        std::unordered_map<std::string, std::string> receiveRequest();

    private:
        int clientSocket; ///< Socket descriptor for the client connection.
        char *buffer; ///< Buffer used for receiving data from the client.
    };

} // namespace ssd

#endif // SERVER_NETWORK_HANDLER_HPP