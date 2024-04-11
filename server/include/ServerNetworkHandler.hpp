#ifndef SERVER_NETWORK_HANDLER_HPP
#define SERVER_NETWORK_HANDLER_HPP

#include <iostream>
#include <unordered_map>

#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

namespace ssd {

#define BUFFER_SIZE 96

    class ServerNetworkHandler {
    public:
        explicit ServerNetworkHandler(int);

        ServerNetworkHandler(const ServerNetworkHandler &) = delete;

        ServerNetworkHandler& operator=(const ServerNetworkHandler &) = delete;

        ServerNetworkHandler(ServerNetworkHandler &&) noexcept;

        ServerNetworkHandler& operator=(ServerNetworkHandler &&) noexcept;

        ~ServerNetworkHandler();

        void sendResponse(const std::unordered_map<std::string, std::string> &) const;

        std::unordered_map<std::string, std::string> receiveRequest();

    private:
        int clientSocket;
        char *buffer;
    };

} // ssd namespace

#endif // SERVER_NETWORK_HANDLER_HPP
