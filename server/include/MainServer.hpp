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

/**
 * @class MainServer
 * @brief The main server application managing client connections.
 *
 * This class initializes the server socket, listens for client connections,
 * and spawns threads to handle each client connection.
 */
    class MainServer {
    public:
        /**
         * @brief Constructs a new Main Server object.
         * @param host The hostname or IP address on which the server will listen.
         * @param port The port on which the server will listen.
         */
        MainServer(const std::string &host, short unsigned port);

        /**
         * @brief Runs the server, accepting client connections.
         * @param range The range within which the number to be guessed is generated.
         * @param initialAttemptsCount Initial number of attempts allowed for the game.
         */
        void run(const NumberRange &range, int initialAttemptsCount);

    private:
        const std::string &host; ///< The hostname or IP address of the server.
        const unsigned short port; ///< The port on which the server listens.
        int server_socket; ///< The server socket for accepting client connections.
    };

} // ssd namespace


#endif // MAIN_SERVER_HPP
