#ifndef UTILS_H
#define UTILS_H

#include "VMConstants.hpp"

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
using namespace std;

bool isValidArguments(const int argc, const char* const argv[]);
void displayUsage();

void removeComments(string& line);
void stripNewlines(string& line);
vector<string> splitString(string& line, const char separator = ' ');

template <typename T>
string processToString(const T& data);

#include "utils.tpp"

#endif
