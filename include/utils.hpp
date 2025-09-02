#ifndef UTILS_H
#define UTILS_H

#include "VMConstants.hpp"

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

namespace Translator {

bool isValidArguments(const int argc, const char* const argv[]);
void displayUsage();

void removeComments(std::string& line);
void stripNewlines(std::string& line);
std::vector<std::string> splitString(std::string& line, const char separator = ' ');

template <typename T>
std::string processToString(const T& data);

#include "utils.tpp"

}

#endif
