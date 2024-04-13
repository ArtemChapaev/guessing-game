#ifndef MAIN_CLIENT_H
#define MAIN_CLIENT_H

#include <unordered_map>

#include "ClientNetworkHandler.hpp"
#include "UserInterface.hpp"

namespace ssd {

    class MainClient {
    public:
        MainClient(const std::string &, const unsigned short);

        void startGame(const std::string &);

    private:
        ClientNetworkHandler networkHandler;

        static std::unordered_map<std::string, std::string> createInitialRequest(const std::string &);

        static std::unordered_map<std::string, std::string> createRequest(Questions, int);

        static void processResponse(const std::unordered_map<std::string, std::string> &, bool &, int &);
    };

} // ssd namespace

#endif // MAIN_CLIENT_H
