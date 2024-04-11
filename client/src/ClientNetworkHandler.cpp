#include "ClientNetworkHandler.hpp"

namespace ssd {

    ClientNetworkHandler::ClientNetworkHandler(
            const std::string &host,
            const unsigned short port
    ) :
            host(host),
            port(port),
            server_socket(socket(AF_INET, SOCK_STREAM, 0)) {
        if (server_socket < 0) {
            throw std::runtime_error("[Client::Client] socket call error");
        }

        buffer = new char[BUFFER_SIZE];
    }

    ClientNetworkHandler::~ClientNetworkHandler() {
        delete[] buffer;
        shutdown(server_socket, SHUT_RDWR);
        close(server_socket);
    }

    void ClientNetworkHandler::connectToServer() {
        sockaddr_in server_address;
        memset(reinterpret_cast<char *>(&server_address), '\0', sizeof(server_address));

        server_address.sin_family = AF_INET;

        hostent *host_name = gethostbyname(host.c_str());
        if (host_name == nullptr) {
            throw std::runtime_error("[ClientNetworkHandler::connectToServer] gethostbyname call error");
        }
        memcpy(&server_address.sin_addr.s_addr, host_name->h_addr, host_name->h_length);

        server_address.sin_port = htons(port);

        if (connect(server_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) != 0) {
            throw std::runtime_error("[ClientNetworkHandler::connectToServer] connect call error");
        }
    }

    void ClientNetworkHandler::sendRequest(const std::unordered_map<std::string, std::string> &keyValuePairs) const {
        auto message = map2str(keyValuePairs);

        ssize_t data_size = send(server_socket, message.c_str(), message.size(), 0);
        if (data_size < 0) {
            throw std::runtime_error("[ClientNetworkHandler::sendRequest] send call error");
        }
    }

    std::unordered_map<std::string, std::string> ClientNetworkHandler::receiveResponse() {
        std::unordered_map<std::string, std::string> result;
        std::string receivedMessage;

        bool isFinish = false;
        while (!isFinish) {
            ssize_t data_size = recv(server_socket, buffer, BUFFER_SIZE, 0);

            if (data_size < 0) {
                throw std::runtime_error("[ClientNetworkHandler::receiveResponse] recv call error");
            }
            std::cout << "[ClientNetworkHandler::receiveResponse] Got " << data_size << " b" << std::endl;

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
