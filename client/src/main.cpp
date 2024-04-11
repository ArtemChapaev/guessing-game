#include <iostream>
#include <unistd.h>

#include "MainClient.hpp"

int main(int argc, char **argv) {
    int opt;
    std::string host = "localhost";
    short unsigned port = 64028u;
    std::string name = "name";

    while ((opt = getopt(argc, argv, "h:p:n")) != -1) {
        switch (opt) {
            case 'h':
                host = optarg;
                break;
            case 'p':
                port = static_cast<unsigned short>(std::atoi(optarg));
                break;
            case 'n':
                name = optarg;
                break;
            default:
                break;
        }
    }

    ssd::MainClient mainClient(host, port);
    mainClient.startGame(name);

    return 0;
}
