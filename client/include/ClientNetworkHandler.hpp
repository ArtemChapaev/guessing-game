#ifndef CLIENT_NETWORK_HANDLER_HPP
#define CLIENT_NETWORK_HANDLER_HPP

#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <unordered_map>
#include "parser.hpp"

namespace ssd {

#define BUFFER_SIZE 96

/**
 * @class ClientNetworkHandler
 * @brief Handles network communication between the client and server.
 *
 * This class manages the network connections and data transmission to the server, including sending requests
 * and receiving responses. It uses TCP sockets for communication.
 */
    class ClientNetworkHandler {
    public:
        /**
         * @brief Constructs a new Client Network Handler object.
         * @param host The server hostname.
         * @param port The server port.
         * @exception std::runtime_error Thrown if the socket cannot be created.
         */
        ClientNetworkHandler(const std::string &host, const unsigned short port);

        /**
         * @brief Destroys the Client Network Handler object.
         *
         * Closes the socket and releases all resources.
         */
        ~ClientNetworkHandler();

        // Delete the copy constructor
        ClientNetworkHandler(const ClientNetworkHandler &) = delete;

        // Delete the assignment operator
        ClientNetworkHandler &operator=(const ClientNetworkHandler &) = delete;

        /**
         * @brief Connects to the server using TCP sockets.
         *
         * @exception std::runtime_error Thrown if connection fails.
         */
        void connectToServer();

        /**
         * @brief Sends a request to the server.
         *
         * @param keyValuePairs A map containing the request parameters.
         * @exception std::runtime_error Thrown if the send operation fails.
         */
        void sendRequest(const std::unordered_map<std::string, std::string> &keyValuePairs) const;

        /**
         * @brief Receives a response from the server.
         *
         * @return std::unordered_map<std::string, std::string> A map containing the response data.
         * @exception std::runtime_error Thrown if there is an error receiving data.
         */
        std::unordered_map<std::string, std::string> receiveResponse();

    private:
        const std::string &host; ///< Server host address.
        const unsigned short port; ///< Server port number.
        int server_socket; ///< Socket descriptor for the server connection.

        char *buffer; ///< Buffer for receiving data from the server.
    };

} // namespace ssd

#endif // CLIENT_NETWORK_HANDLER_HPP
