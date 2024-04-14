#ifndef CLIENT_HANDLER_HPP
#define CLIENT_HANDLER_HPP

#include <unordered_map>
#include <mutex>

#include "parser.hpp"
#include "ServerNetworkHandler.hpp"
#include "Questions.hpp"
#include "GameManager.hpp"
#include "NumberRange.hpp"

namespace ssd {

#define BUFFER_SIZE 96

/**
 * @class ClientHandler
 * @brief Manages communication and game logic for each connected client.
 *
 * This class is responsible for handling all interactions with a connected client. It processes incoming
 * requests, manages game state, and sends responses back to the client. It is designed to be run in a separate
 * thread for each client.
 */
    class ClientHandler {
    public:
        /**
         * @brief Constructs a new Client Handler object.
         * @param socket The socket descriptor associated with the connected client.
         */
        ClientHandler(int socket);

        // Delete the copy constructor
        ClientHandler(const ClientHandler &) = delete;

        // Delete the assignment operator
        ClientHandler &operator=(const ClientHandler &) = delete;

        /**
         * @brief Main loop to handle client requests and game logic.
         * @param range The range within which the number to be guessed is generated.
         * @param initialAttemptsCount Initial number of attempts allowed for the game.
         */
        void run(const NumberRange &range, int initialAttemptsCount);

    private:
        ServerNetworkHandler networkHandler; ///< Handles network communication with the client.

        /**
         * @brief Processes a single game request from the client.
         * @param request The request received from the client.
         * @param question The type of question asked by the client.
         * @param questionValue The numerical value associated with the question.
         */
        void processRequest(const std::unordered_map<std::string, std::string> &request, Questions &question, int &questionValue);

        /**
         * @brief Creates the initial response to send to the client after the game starts.
         * @param game Reference to the GameManager managing the game logic.
         * @return std::unordered_map<std::string, std::string> The response containing game start information.
         */
        std::unordered_map<std::string, std::string> createInitialResponse(const GameManager &game);

        /**
         * @brief Creates a response based on the result of a client's question.
         * @param game Reference to the GameManager managing the game logic.
         * @param question The type of question asked.
         * @param questionAnswer The result of the question (true if correct).
         * @return std::unordered_map<std::string, std::string> The response to be sent to the client.
         */
        std::unordered_map<std::string, std::string> createResponse(const GameManager &game, Questions question, bool questionAnswer);
    };

} // namespace ssd

#endif // CLIENT_HANDLER_HPP
