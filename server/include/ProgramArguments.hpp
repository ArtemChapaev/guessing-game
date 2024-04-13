#ifndef PROGRAM_ARGUMENTS_HPP
#define PROGRAM_ARGUMENTS_HPP

#include <unistd.h>
#include <string>
#include <ctime>

#include "NumberRange.hpp"

struct ProgramArguments {
    std::string host = "localhost";
    short unsigned port = 1024u;
    long seed = time(nullptr);
    int attemptsCount = 5;
    ssd::NumberRange range = {1, 10, 25, 30};
};


ProgramArguments parseArguments(int argc, char **argv) {
    int opt;
    ProgramArguments args;

    int ll = args.range.getLowLeftBorder();
    int hl = args.range.getHighLeftBorder();
    int lr = args.range.getLowRightBorder();
    int hr = args.range.getHighRightBorder();
    while ((opt = getopt(argc, argv, "h:p:s:n:l:L:r:R:")) != -1) {
        switch (opt) {
            case 'h':
                args.host = optarg;
                break;
            case 'p':
                try {
                    args.port = static_cast<unsigned short>(std::stoi(optarg));
                } catch (const std::invalid_argument &) {
                    throw std::invalid_argument("[::parseArguments] Port can be unsigned short");
                }
                break;
            case 's':
                try {
                    args.seed = std::stol(optarg);
                } catch (const std::invalid_argument &) {
                    throw std::invalid_argument("[::parseArguments] Seed can be long");
                }
                break;
            case 'n':
                try {
                    args.attemptsCount = std::stoi(optarg);
                } catch (const std::invalid_argument &) {
                    throw std::invalid_argument("[::parseArguments] Attempts count can be unsigned int");
                }
                if (args.attemptsCount < 0) {
                    throw std::invalid_argument("[::parseArguments] Attempts count can be bigger than 0");
                }
                break;
            case 'l':
                try {
                    ll = std::stoi(optarg);
                } catch (const std::invalid_argument &) {
                    throw std::invalid_argument("[::parseArguments] Low left border count can be int");
                }
                break;
            case 'L':
                try {
                    hl = std::stoi(optarg);
                } catch (const std::invalid_argument &) {
                    throw std::invalid_argument("[::parseArguments] High left border count can be int");
                }
                break;
            case 'r':
                try {
                    lr = std::stoi(optarg);
                } catch (const std::invalid_argument &) {
                    throw std::invalid_argument("[::parseArguments] Low right border count can be int");
                }
                break;
            case 'R':
                try {
                    hr = std::stoi(optarg);
                } catch (const std::invalid_argument &) {
                    throw std::invalid_argument("[::parseArguments] High right border count can be int");
                }
                break;
            default:
                break;
        }

    }
    args.range.setBorders(ll, hl, lr, hr);

    return args;
}

#endif // PROGRAM_ARGUMENTS_HPP
