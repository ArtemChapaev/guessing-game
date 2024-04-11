#include "MainServer.hpp"

#include <iostream>

namespace ssd {
    MainServer::MainServer(const std::string &h, short unsigned p) :
            host(h),
            port(p),
            server_socket(socket(AF_INET, SOCK_STREAM, 0)) {
        if (server_socket < 0) {
            throw std::runtime_error("[ServerNetworkHandler::ServerNetworkHandler] socket(2) call error");
        }

        sockaddr_in server_address;
        memset(reinterpret_cast<char *>(&server_address), '\0', sizeof(server_address));

        server_address.sin_family = AF_INET;

        hostent *host_name;
        host_name = gethostbyname(host.c_str());
        if (host_name == nullptr) {
            throw std::runtime_error("[ServerNetworkHandler::ServerNetworkHandler] gethostbyname(3) call error");
        }
        memcpy(&server_address.sin_addr.s_addr, host_name->h_addr, host_name->h_length);

        server_address.sin_port = htons(port);

        if (bind(server_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) != 0) {
            throw std::runtime_error("[ServerNetworkHandler::ServerNetworkHandler] bind(2) call error");
        }

        std::cout << "[ServerNetworkHandler::ServerNetworkHandler] Ready on " << host << ":" << port << std::endl;
    }


    void MainServer::run(const NumberRange &range, int attemptsCount) {
        if (listen(server_socket, CONNECTION_QUEUE_SIZE) != 0) {
            throw std::runtime_error("[ServerNetworkHandler::run] listen(2) call error");
        }

        int clientIdCounter = 0;
        while (1) {
            sockaddr client_address;
            socklen_t address_size = sizeof(client_address);

            int clientSocket = accept(server_socket, &client_address, &address_size);

            if (clientSocket < 0) {
                throw std::runtime_error("[ServerNetworkHandler::run] accept(2) call error");
            }
            printClientInfo(client_address);

            clients.emplace_back(clientSocket, clientIdCounter++);
            auto thread = std::thread(&ClientHandler::run,
                        &clients.back(),
                        range,
                        attemptsCount
            );

            thread.detach();

            if (clientIdCounter % CLIENTS_CHECK_FREQ == 0) {
                mtx.lock();
                if (finishedClients.size()) {
                    checkClients();
                }
                mtx.unlock();
            }
        }
        // unreachable
    }

    void MainServer::printClientInfo(sockaddr &client_address) {
        char *clientHost = inet_ntoa(reinterpret_cast<sockaddr_in *>(&client_address)->sin_addr);
        unsigned short clientPort = ntohs(reinterpret_cast<sockaddr_in *>(&client_address)->sin_port);
        std::cout << "[ServerNetworkHandler::printClientInfo] New connection from " << clientHost
                  << ":" << clientPort << std::endl;
    }

    void MainServer::checkClients() {
        for (auto it = clients.begin(); it != clients.end();) {
            auto ID = it->clientId;
            if (finishedClients.find(ID) != finishedClients.end()) {
                finishedClients.erase(ID);
                it = clients.erase(it);
            } else {
                ++it;
            }
        }
    }

} // ssd namespace
