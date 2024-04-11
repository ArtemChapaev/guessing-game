#ifndef PROGRAM_ARGUMENTS_HPP
#define PROGRAM_ARGUMENTS_HPP

#include <unistd.h>
#include <string>

#include "NumberRange.hpp"

struct ProgramArguments {
    std::string host = "localhost";
    short unsigned port = 64028u;
    int seed = 33;
    int attemptsCount = 5;
    ssd::NumberRange range;
};


ProgramArguments parseArguments(int argc, char** argv) {
    int opt;
    ProgramArguments args;

    // add checks

    while ((opt = getopt(argc, argv, "a:p:s:n:l:L:h:H")) != -1) {
        switch (opt) {
            case 'a':
                args.host = optarg;
                break;
            case 'p':
                args.port = static_cast<unsigned short>(std::atoi(optarg));
                break;
            case 's':
                args.seed = std::atoi(optarg);
                break;
            case 'n':
                args.attemptsCount = std::atoi(optarg);
                break;
            case 'l':
                args.range.lowLeftBorder = std::atoi(optarg);
                break;
            case 'L':
                args.range.highLeftBorder = std::atoi(optarg);
                break;
            case 'h':
                args.range.lowRightBorder = std::atoi(optarg);
                break;
            case 'H':
                args.range.highRightBorder = std::atoi(optarg);
                break;
            default:
                break;
        }
    }

    return args;
}

#endif // PROGRAM_ARGUMENTS_HPP
