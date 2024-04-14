#ifndef MAIN_CLIENT_H
#define MAIN_CLIENT_H

#include <unordered_map>
#include <string>

#include "ClientNetworkHandler.hpp"
#include "UserInterface.hpp"

namespace ssd {

/**
 * @class MainClient
 * @brief The main client application managing the game flow.
 *
 * This class initializes the connection with the server, manages game flow and processes user inputs and server responses.
 */
    class MainClient {
    public:
        /**
         * @brief Constructs a new Main Client object.
         * @param host The hostname of the server.
         * @param port The port on which the server is running.
         */
        MainClient(const std::string &host, const unsigned short port);

        /**
         * @brief Starts the game with the provided player name.
         * @param name The player's name.
         */
        void startGame(const std::string &name);

    private:
        ClientNetworkHandler networkHandler;  ///< Handles network communication with the server.

        /**
         * @brief Creates the initial request to start a game session.
         * @param name The player's name.
         * @return std::unordered_map<std::string, std::string> The request map with starting parameters.
         */
        static std::unordered_map<std::string, std::string> createInitialRequest(const std::string &name);

        /**
         * @brief Creates a request based on user input.
         * @param question The type of question being asked.
         * @param questionArgument The value associated with the question.
         * @return std::unordered_map<std::string, std::string> The request map with question details.
         */
        static std::unordered_map<std::string, std::string> createRequest(Questions question, int questionArgument);

        /**
         * @brief Processes the response from the server.
         * @param response The server's response as a map.
         * @param questionAnswer Indicates whether the user's guess was correct.
         * @param gameResult Indicates the result of the game; 1 for win, -1 for loss, 0 for ongoing.
         */
        static void processResponse(const std::unordered_map<std::string, std::string> &response, bool &questionAnswer, int &gameResult);
    };

} // namespace ssd

#endif // MAIN_CLIENT_H
