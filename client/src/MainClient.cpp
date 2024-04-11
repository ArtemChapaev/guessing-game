#include "MainClient.hpp"

namespace ssd {

    MainClient::MainClient(
            const std::string &host,
            const unsigned short port
    ) : networkHandler(host, port), userInterface(), gameResult(0) {}

    MainClient::~MainClient() {
        if (gameResult == 0) {
            std::unordered_map<std::string, std::string> keyValuePairs;
            keyValuePairs["type"] = "quit";
            networkHandler.sendRequest(keyValuePairs);
        }
    }

    void MainClient::startGame(const std::string &name) {
        networkHandler.connectToServer();
        userInterface.prepareDisplay();

        auto request = createInitialRequest(name);

        networkHandler.sendRequest(request);
        auto response = networkHandler.receiveResponse();

        // answer["type"] == "generated_number"
        userInterface.displayMessage(
                std::stoi(response["left_border"]),
                std::stoi(response["right_border"]),
                std::stoi(response["left_attempts"])
        );

        while (!gameResult) {
            auto userInput = userInterface.getUserInput();
            auto question = userInput.first;
            auto questionArgument = userInput.second;

            networkHandler.sendRequest(createRequest(question, questionArgument));
            response = networkHandler.receiveResponse();

            bool questionAnswer = false;
            processResponse(response, questionAnswer, gameResult);
            userInterface.displayMessage(
                    question,
                    questionAnswer,
                    questionArgument,
                    std::stoi(response["left_attempts"])
            );
        }
        if (gameResult == 1) {
            userInterface.displayWin();
        } else {
            userInterface.displayLoss();
        }
    }

    void MainClient::processResponse(
            const std::unordered_map<std::string, std::string> &response,
            bool &questionAnswer,
            int &gameResult
    ) {
        std::string response_type = response.find("type")->second;
        std::string response_status = response.find("status")->second;

        if (response_type == "guess_result" && response_status == "correct") {
            gameResult = 1;
        } else if (std::stoi(response.find("left_attempts")->second) == 0) {
            gameResult = -1;
        } else if (response_status == "correct") {
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
