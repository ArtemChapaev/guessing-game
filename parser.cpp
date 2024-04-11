#include "parser.hpp"

std::unordered_map<std::string, std::string> str2map(const std::string &input) {
    if (input.back() != '.') {
        throw std::runtime_error("Input string does not end with a period.");
    }

    std::unordered_map<std::string, std::string> keyValuePairs;
    size_t start = 0;
    size_t end = 0;

    while ((end = input.find(',', start)) != std::string::npos) {
        auto pair = input.substr(start, end - start);
        auto delimiterPos = pair.find(':');
        if (delimiterPos != std::string::npos) {
            auto key = pair.substr(0, delimiterPos);
            auto value = pair.substr(delimiterPos + 1);
            keyValuePairs[key] = value;
        }
        start = end + 1;
    }

    auto lastPair = input.substr(start, input.size() - start - 1);
    auto delimiterPos = lastPair.find(':');
    if (delimiterPos != std::string::npos) {
        auto key = lastPair.substr(0, delimiterPos);
        auto value = lastPair.substr(delimiterPos + 1);
        keyValuePairs[key] = value;
    }

    return keyValuePairs;
}

std::string map2str(const std::unordered_map<std::string, std::string> &keyValuePairs) {
    std::string result;

    for (const auto &pair: keyValuePairs) {
        result += pair.first + ':' + pair.second + ',';
    }

    if (!result.empty()) {
        result.pop_back();
    }

    result += '.';

    return result;
}
