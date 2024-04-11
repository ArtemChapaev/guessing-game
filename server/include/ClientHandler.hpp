#ifndef CLIENT_HANDLER_HPP
#define CLIENT_HANDLER_HPP

#include <unordered_map>
#include <unordered_set>
#include <mutex>

#include "parser.hpp"

#include "ServerNetworkHandler.hpp"
#include "Questions.hpp"
#include "GameManager.hpp"
#include "NumberRange.hpp"

extern std::unordered_set<int> finishedClients;
extern std::mutex mtx;

namespace ssd {

#define BUFFER_SIZE 96

    class ClientHandler {
    public:
        ClientHandler(int, int);

        ~ClientHandler();

        ClientHandler(const ClientHandler &) = delete;

        ClientHandler& operator=(const ClientHandler &) = delete;

        ClientHandler(ClientHandler &&) noexcept;

        ClientHandler& operator=(ClientHandler &&) = delete;

        void run(const NumberRange &, int);

        std::unordered_map<std::string, std::string> createInitialResponse(const GameManager &);

        std::unordered_map<std::string, std::string> createResponse(const GameManager &, Questions, bool);

        void processRequest(const std::unordered_map<std::string, std::string> &, Questions &, int &);

        const int clientId;

    private:
        ServerNetworkHandler networkHandler;
        bool isFinish;
    };

} // ssd namespace

#endif // CLIENT_HANDLER_HPP
