#ifndef PARSER_HPP
#define PARSER_HPP

#include <unordered_map>
#include <string>

std::unordered_map<std::string, std::string> str2map(const std::string &input);
std::string map2str(const std::unordered_map<std::string, std::string>& keyValuePairs);

#endif // PARSER_HPP
