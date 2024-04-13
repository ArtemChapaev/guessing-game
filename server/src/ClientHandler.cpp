#include "ClientHandler.hpp"

namespace ssd {

    ClientHandler::ClientHandler(
            int socket
    ) : networkHandler(socket) {}

    void ClientHandler::run(
            const NumberRange &range,
            int initialAttemptsCount
    ) {
        std::unordered_map<std::string, std::string> request = networkHandler.receiveRequest();
        // type == "start". ignore user's name
        std::cout << "[ClientHandler::run] Game is started, client's name: " << request["name"] << std::endl;

        GameManager game(range, initialAttemptsCount);
        // send data about generated number to user
        networkHandler.sendResponse(createInitialResponse(game));

        Questions question;
        int questionValue;

        bool isFinish = false;
        // while game is not finished read user's question -> process it -> send aswer
        while (!isFinish) {
            try {
                request = networkHandler.receiveRequest();
            } catch (const std::runtime_error &e) {
                // if client went to sleep, we left loop and delete thread
                break;
            }
            processRequest(request, question, questionValue);

            bool questionAnswer = game.checkQuestion(question, questionValue);
            networkHandler.sendResponse(
                    createResponse(
                            game,
                            question,
                            questionAnswer
                    )
            );

            // conditions of game's end
            if (question == Questions::equal && questionAnswer || game.getLeftAttempts() == 0) {
                isFinish = true;
            }
        }
        std::cout << "[ClientHandler::run] Game is finished, client's name: " << request["name"] << std::endl;
    }

    void ClientHandler::processRequest(
            const std::unordered_map<std::string, std::string> &request,
            Questions &question,
            int &questionValue
    ) {
        auto requestType = request.find("type")->second;

        if (requestType == "guess") {
            question = Questions::equal;
        } else if (requestType == "less_question") {
            question = Questions::less;
        } else {
            question = Questions::bigger;
        }

        questionValue = std::stoi(request.find("number")->second);
    }

    std::unordered_map<std::string, std::string> ClientHandler::createInitialResponse(
            const GameManager &game
    ) {
        std::unordered_map<std::string, std::string> keyValuePairs;
        auto numberBorders = game.getNumberBorders();

        // add info about generated number
        keyValuePairs["type"] = "generated_number";
        keyValuePairs["left_border"] = std::to_string(numberBorders.first);
        keyValuePairs["right_border"] = std::to_string(numberBorders.second);
        keyValuePairs["left_attempts"] = std::to_string(game.getLeftAttempts());

        return keyValuePairs;
    }

    std::unordered_map<std::string, std::string> ClientHandler::createResponse(
            const GameManager &game,
            Questions question,
            bool questionAnswer
    ) {
        std::unordered_map<std::string, std::string> keyValuePairs;
        // define type
        if (question == Questions::equal) {
            keyValuePairs["type"] = "guess_result";
        } else if (question == Questions::less) {
            keyValuePairs["type"] = "less_question_result";
        } else {
            keyValuePairs["type"] = "bigger_question_result";
        }

        // define status
        if (questionAnswer) {
            keyValuePairs["status"] = "correct";
        } else {
            keyValuePairs["status"] = "wrong";
        }

        keyValuePairs["left_attempts"] = std::to_string(game.getLeftAttempts());
        return keyValuePairs;
    }

} // ssd namespace
