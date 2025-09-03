#ifndef UTILS_H
#define UTILS_H

#include "VMConstants.hpp"

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

namespace Translator {

/**
 * Validates the command-line arguments and flags provided in the executable call.
 */
bool isValidArguments(const int argc, const char* const argv[]);

/**
 * Displays an error message showing the correct usage of the translator.
 */
void displayUsage();

/**
 * Removes C++/Java-style single line comments from the provided string in place.
 */
void removeComments(std::string& line);

/**
 * Removes \r characters from the input to make line processing uniform between LF and CRLF files.
 */
void stripNewlines(std::string& line);

/**
 * Splits the provided string using the provided separator as a delimiter and
 * returns a vector containing each element.
 */
std::vector<std::string> splitString(std::string& line, const char separator = ' ');

template <typename T>
std::string processToString(const T& data);

#include "utils.tpp"

}

#endif
