#ifndef PROGRAM_ARGUMENTS_HPP
#define PROGRAM_ARGUMENTS_HPP

#include <unistd.h>
#include <string>
#include <ctime>
#include "NumberRange.hpp"

/**
 * @struct ProgramArguments
 * @brief Holds all configurable options for the program.
 *
 * This structure stores the values of various command-line parameters.
 */
struct ProgramArguments {
    std::string host = "localhost"; ///< Default host address of the server.
    unsigned short port = 1024u;    ///< Default port number for server connection.
    long seed = time(nullptr);      ///< Seed for the random number generator, defaults to current time.
    int attemptsCount = 5;          ///< Default number of attempts per 25 number range.
    ssd::NumberRange range = {1, 10, 25, 30}; ///< Default number range for game.
};

/**
 * @brief Parses command-line arguments to configure the program settings.
 *
 * This function interprets command-line options and fills a ProgramArguments struct with the specified values.
 * It handles a variety of settings such as server address, port, random seed, and game parameters.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return ProgramArguments A fully populated ProgramArguments struct.
 * @exception std::invalid_argument Thrown if any argument is invalid or improperly formatted.
 */
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
