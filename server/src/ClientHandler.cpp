#include "ClientHandler.hpp"

std::unordered_set<int> finishedClients;
std::mutex mtx;

namespace ssd {

    ClientHandler::ClientHandler(int socket, int id) : clientId(id), networkHandler(socket), isFinish(false) {}

    ClientHandler::~ClientHandler() {
        if (!isFinish) {
            std::unordered_map<std::string, std::string> keyValuePairs;
            keyValuePairs["type"] = "quit";
            networkHandler.sendResponse(keyValuePairs);
        }
        std::cout << "[ClientHandler::~ClientHandler] game over" << std::endl;
    }

    ClientHandler::ClientHandler(ClientHandler && other) noexcept : clientId(other.clientId), networkHandler(std::move(other.networkHandler)), isFinish(other.isFinish) {}

    void ClientHandler::run(const NumberRange& range, int attemptsCount) {
        GameManager game(range, attemptsCount);

        std::unordered_map<std::string, std::string> request = networkHandler.receiveRequest();
        // type == "start". ignore user's name
        std::cout << "[ClientHandler::run] Clients name: " << request["name"] << std::endl;
        networkHandler.sendResponse(createInitialResponse(game));

        Questions question;
        int questionValue;

        while (!isFinish) {
            request = networkHandler.receiveRequest();

            processRequest(request, question, questionValue);
            if (isFinish) {
                break;
            }
            bool questionAnswer = game.checkQuestion(question, questionValue);
            auto response = createResponse(game, question, questionAnswer);
            networkHandler.sendResponse(response);

            if (question == Questions::equal && questionAnswer || game.getLeftAttempts() == 0) {
                isFinish = true;
            }
        }

        std::cout << "[ClientHandler::run] game over" << std::endl;

        mtx.lock();
        finishedClients.insert(clientId);
        mtx.unlock();
    }

    void ClientHandler::processRequest(
            const std::unordered_map<std::string, std::string> &request,
            Questions &question,
            int &questionValue
    ) {
        auto requestType = request.find("type")->second;

        // if user finish session
        if (requestType == "quit") {
            isFinish = true;
            return;
        }

        if (requestType == "guess") {
            question = Questions::equal;
        } else if (requestType == "less_question") {
            question = Questions::less;
        } else {
            question = Questions::bigger;
        }

        questionValue = std::stoi(request.find("number")->second);
    }

    std::unordered_map<std::string, std::string> ClientHandler::createInitialResponse(const GameManager &game) {
        std::unordered_map<std::string, std::string> keyValuePairs;
        auto numberBorders = game.getNumberBorders();

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
        if (question == Questions::equal) {
            keyValuePairs["type"] = "guess_result";
        } else if (question == Questions::less) {
            keyValuePairs["type"] = "less_question_result";
        } else {
            keyValuePairs["type"] = "bigger_question_result";
        }

        if (questionAnswer) {
            keyValuePairs["status"] = "correct";
        } else {
            keyValuePairs["status"] = "wrong";
        }

        keyValuePairs["left_attempts"] = std::to_string(game.getLeftAttempts());
        return keyValuePairs;
    }

} // ssd namespace
