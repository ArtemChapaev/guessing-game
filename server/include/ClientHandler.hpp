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

namespace ssd {

#define BUFFER_SIZE 96

    class ClientHandler {
    public:
        ClientHandler(int);

        ClientHandler(const ClientHandler &) = delete;

        ClientHandler& operator=(const ClientHandler &) = delete;

        void run(const NumberRange &, int);
    private:
        ServerNetworkHandler networkHandler;

        void processRequest(const std::unordered_map<std::string, std::string> &, Questions &, int &);

        std::unordered_map<std::string, std::string> createInitialResponse(const GameManager &);

        std::unordered_map<std::string, std::string> createResponse(const GameManager &, Questions, bool);

    };

} // ssd namespace

#endif // CLIENT_HANDLER_HPP
