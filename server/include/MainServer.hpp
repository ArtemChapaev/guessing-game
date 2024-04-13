#ifndef MAIN_SERVER_HPP
#define MAIN_SERVER_HPP

#include <thread>
#include <iostream>

#include <netdb.h>
#include <arpa/inet.h>

#include "NumberRange.hpp"
#include "ClientHandler.hpp"

namespace ssd {

#define CONNECTION_QUEUE_SIZE 4000

    class MainServer {
    public:
        MainServer(const std::string &, short unsigned);

        void run(const NumberRange &, int);

    private:
        const std::string &host;
        const unsigned short port;
        int server_socket;
    };

} // ssd namespace


#endif // MAIN_SERVER_HPP
