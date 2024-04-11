#ifndef MAIN_SERVER_HPP
#define MAIN_SERVER_HPP

#include <list>
#include <thread>

#include <netdb.h>
#include <arpa/inet.h>

#include "NumberRange.hpp"
#include "ClientHandler.hpp"

extern std::unordered_set<int> finishedClients;
extern std::mutex mtx;

namespace ssd {

#define CONNECTION_QUEUE_SIZE 4000
#define CLIENTS_CHECK_FREQ 5

    class MainServer {
    public:
        MainServer(const std::string &, short unsigned);

        void run(const NumberRange &, int);

    private:
        const std::string &host;
        const unsigned short port;
        int server_socket;

        std::list<ClientHandler> clients;

        void printClientInfo(sockaddr &);

        void checkClients();
    };

} // ssd namespace


#endif // MAIN_SERVER_HPP
