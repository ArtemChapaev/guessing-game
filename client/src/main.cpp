#include <unistd.h>

#include "MainClient.hpp"

int main(int argc, char **argv) {
    int opt;
    std::string host = "localhost";
    short unsigned port = 1024u;
    std::string name = "Тамара Михайловна";

    while ((opt = getopt(argc, argv, "h:p:n:")) != -1) {
        switch (opt) {
            case 'h':
                host = optarg;
                break;
            case 'p':
                try {
                    port = static_cast<unsigned short>(std::stoi(optarg));
                } catch (const std::invalid_argument&) {
                    throw std::invalid_argument("[::main] Port can be unsigned short");
                }
                break;
            case 'n':
                name = optarg;
                break;
            default:
                break;
        }
    }

    try {
        ssd::MainClient mainClient(host, port);
        mainClient.startGame(name);
    } catch(const std::runtime_error& e) {
        std::cerr << "Client application error: " << e.what() << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "Client application error: unexpected error" << std::endl;
        return 2;
    }
    return 0;
}
