#ifndef CLIENT_NETWORK_HANDLER_HPP
#define CLIENT_NETWORK_HANDLER_HPP

#include <iostream>

#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "parser.hpp"

namespace ssd {

#define BUFFER_SIZE 96

    class ClientNetworkHandler {
    public:
        ClientNetworkHandler(const std::string &, const unsigned short);

        ~ClientNetworkHandler();

        ClientNetworkHandler(const ClientNetworkHandler &) = delete;

        ClientNetworkHandler operator=(const ClientNetworkHandler &) = delete;

        void connectToServer();

        void sendRequest(const std::unordered_map<std::string, std::string> &) const;

        std::unordered_map<std::string, std::string> receiveResponse();

    private:
        const std::string &host;
        const unsigned short port;
        int server_socket;

        char *buffer;
    };

} // ssd namespace

#endif // CLIENT_NETWORK_HANDLER_HPP
