#include "ServerNetworkHandler.hpp"

namespace ssd {

    ServerNetworkHandler::ServerNetworkHandler(int socket) : clientSocket(socket) {
        buffer = new char[BUFFER_SIZE];
    }

    ServerNetworkHandler::ServerNetworkHandler(ServerNetworkHandler &&other) noexcept {
        clientSocket = other.clientSocket;
        buffer = other.buffer;

        other.buffer = nullptr;
        other.clientSocket = -1;
    }

    ServerNetworkHandler &ServerNetworkHandler::operator=(ServerNetworkHandler &&other) noexcept {
        if (this != &other) {

            clientSocket = other.clientSocket;
            buffer = other.buffer;

            other.buffer = nullptr;
            other.clientSocket = -1;
        }

        return *this;
    }

    ServerNetworkHandler::~ServerNetworkHandler() {
        delete[] buffer;

        if (clientSocket != -1) {
            shutdown(clientSocket, SHUT_RDWR);
            close(clientSocket);
        }

    }

    void ServerNetworkHandler::sendResponse(const std::unordered_map<std::string, std::string> &keyValuePairs) const {
        auto response = map2str(keyValuePairs);

        ssize_t data_size = send(clientSocket, response.c_str(), response.size(), 0);
        if (data_size < 0) {
            throw std::runtime_error("[ServerNetworkHandler::sendResponse] send call error");
        }
    }

    std::unordered_map<std::string, std::string> ServerNetworkHandler::receiveRequest() {
        std::unordered_map<std::string, std::string> result;
        std::string receivedMessage;

        bool isFinish = false;
        while (!isFinish) {
            ssize_t data_size = recv(clientSocket, buffer, BUFFER_SIZE, 0);
            if (data_size <= 0) {
                throw std::runtime_error("[ServerNetworkHandler::receiveRequest] recv call error");
            }
            receivedMessage += std::string(buffer, data_size);
            try {
                result = str2map(receivedMessage);

                // if error isFinish will be store false
                isFinish = true;
            } catch (const std::runtime_error &e) {
            }
        }

        return result;
    }

} // ssd namespace

