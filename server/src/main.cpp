#include "ProgramArguments.hpp"
#include "MainServer.hpp"

extern std::unordered_set<int> finishedClients;
extern std::mutex mtx;

int main(int argc, char** argv) {
    auto args = parseArguments(argc, argv);
    srand(args.seed);

    ssd::MainServer server(args.host, args.port);
    server.run(args.range, args.attemptsCount);
    return 0;
}



