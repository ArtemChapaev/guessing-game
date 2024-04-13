#include "MainClient.hpp"

namespace ssd {

    MainClient::MainClient(
            const std::string &host,
            const unsigned short port
    ) : networkHandler(host, port) {}

    void MainClient::startGame(const std::string &name) {
        networkHandler.connectToServer();
        ssd::UserInterface::prepareDisplay();

        // create first "hello"-request
        networkHandler.sendRequest(createInitialRequest(name));
        auto response = networkHandler.receiveResponse();

        // answer["type"] == "generated_number"
        ssd::UserInterface::displayMessage(
                std::stoi(response["left_border"]),
                std::stoi(response["right_border"]),
                std::stoi(response["left_attempts"])
        );

        int gameResult = 0;
        while (!gameResult) {
            auto userInput = ssd::UserInterface::getUserInput();
            auto question = userInput.first;
            auto questionArgument = userInput.second;

            networkHandler.sendRequest(createRequest(question, questionArgument));
            try {
                response = networkHandler.receiveResponse();
            } catch (const std::runtime_error &e) {
                // if server went to sleep, we display server's error and finish current game
                ssd::UserInterface::displayServerError();
                return;
            }

            bool questionAnswer = false;
            processResponse(response, questionAnswer, gameResult);
            ssd::UserInterface::displayMessage(
                    question,
                    questionAnswer,
                    questionArgument,
                    std::stoi(response["left_attempts"])
            );
        }
        if (gameResult == 1) {
            ssd::UserInterface::displayWin();
        } else {
            ssd::UserInterface::displayLoss();
        }
    }

    void MainClient::processResponse(
            const std::unordered_map<std::string, std::string> &response,
            bool &questionAnswer,
            int &gameResult
    ) {
        std::string response_type = response.find("type")->second;
        std::string response_status = response.find("status")->second;

        // we define
        // 1. is finished game or not
        // 2. what is user question's answer
        if (response_type == "guess_result" && response_status == "correct") {
            gameResult = 1;
        } else if (std::stoi(response.find("left_attempts")->second) == 0) {
            gameResult = -1;
        }

        if (response_status == "correct") {
            questionAnswer = true;
        }
    }

    std::unordered_map<std::string, std::string> MainClient::createInitialRequest(
            const std::string &name
    ) {
        std::unordered_map<std::string, std::string> keyValuePairs;

        keyValuePairs["type"] = "start";
        keyValuePairs["name"] = name;

        return keyValuePairs;
    }

    std::unordered_map<std::string, std::string> MainClient::createRequest(
            Questions question,
            int questionArgument
    ) {
        std::unordered_map<std::string, std::string> keyValuePairs;

        switch (question) {
            case Questions::less: {
                keyValuePairs["type"] = "less_question";
                break;
            }
            case Questions::bigger: {
                keyValuePairs["type"] = "bigger_question";
                break;
            }
            case Questions::equal: {
                keyValuePairs["type"] = "guess";
                break;
            }
            default: {
                // unreachable
            }
        }

        keyValuePairs["number"] = std::to_string(questionArgument);
        return keyValuePairs;
    }

}
