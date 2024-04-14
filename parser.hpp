#ifndef PARSER_HPP
#define PARSER_HPP

#include <unordered_map>
#include <string>
#include <stdexcept>

/**
 * @brief Converts a delimited string into a key-value map.
 *
 * This function parses a string formatted with key-value pairs separated by commas and each key-value separated by a colon.
 * The string must end with a period. Throws std::runtime_error if the string format is incorrect.
 *
 * @param input The string to be converted.
 * @return std::unordered_map<std::string, std::string> A map representing the key-value pairs.
 * @exception std::runtime_error Thrown if the input string does not end with a period.
 */
std::unordered_map<std::string, std::string> str2map(const std::string &input);

/**
 * @brief Converts a key-value map into a delimited string.
 *
 * This function serializes a map of key-value pairs into a string where each pair is separated by a comma and
 * key and value are separated by a colon. The resulting string ends with a period.
 *
 * @param keyValuePairs The map of key-value pairs to be serialized.
 * @return std::string A string representing the serialized key-value pairs.
 */
std::string map2str(const std::unordered_map<std::string, std::string>& keyValuePairs);

#endif // PARSER_HPP
