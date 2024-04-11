#ifndef MAIN_CLIENT_H
#define MAIN_CLIENT_H

#include <unordered_map>

#include "ClientNetworkHandler.hpp"
#include "UserInterface.hpp"

namespace ssd {

    class MainClient {
    public:
        MainClient(const std::string &, const unsigned short);

        ~MainClient();

        void startGame(const std::string &);

    private:
        ClientNetworkHandler networkHandler;
        const UserInterface userInterface;

        int gameResult;

        static std::unordered_map<std::string, std::string> createInitialRequest(const std::string &name);

        static std::unordered_map<std::string, std::string> createRequest(Questions question, int questionArgument);

        static void processResponse(const std::unordered_map<std::string, std::string> &, bool &, int &);
    };

} // ssd namespace

#endif // MAIN_CLIENT_H
