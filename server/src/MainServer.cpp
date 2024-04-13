#include "MainServer.hpp"

namespace ssd {
    MainServer::MainServer(const std::string &h, short unsigned p) :
            host(h),
            port(p),
            server_socket(socket(AF_INET, SOCK_STREAM, 0)) {
        if (server_socket < 0) {
            throw std::runtime_error("[ServerNetworkHandler::ServerNetworkHandler] socket call error");
        }

        // prepare to bind socket
        sockaddr_in server_address;
        memset(reinterpret_cast<char *>(&server_address), '\0', sizeof(server_address));

        server_address.sin_family = AF_INET;

        hostent *host_name;
        host_name = gethostbyname(host.c_str());
        if (host_name == nullptr) {
            throw std::runtime_error("[ServerNetworkHandler::ServerNetworkHandler] gethostbyname call error");
        }
        memcpy(&server_address.sin_addr.s_addr, host_name->h_addr, host_name->h_length);

        server_address.sin_port = htons(port);

        if (bind(server_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) != 0) {
            throw std::runtime_error("[ServerNetworkHandler::ServerNetworkHandler] bind call error");
        }

        std::cout << "[ServerNetworkHandler::ServerNetworkHandler] Ready on " << host << ":" << port << std::endl;
    }


    void MainServer::run(const NumberRange &range, int initialAttemptsCount) {
        if (listen(server_socket, CONNECTION_QUEUE_SIZE) != 0) {
            throw std::runtime_error("[ServerNetworkHandler::run] listen call error");
        }

        while (1) {
            int clientSocket = accept(server_socket, nullptr, nullptr);

            if (clientSocket < 0) {
                std::cout << "[ServerNetworkHandler::run] accept error call "<< std::endl;
                continue;
            }

            // create thread for new user and go to waiting new user in next iteration
            std::thread thread([this, clientSocket, range, initialAttemptsCount] () {
                ClientHandler client(clientSocket);
                client.run(range, initialAttemptsCount);
            });

            thread.detach();
        }
        // unreachable
    }

} // ssd namespace
