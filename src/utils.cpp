#include "utils.hpp"

#include <regex>
#include <string>
#include <vector>
using namespace std;

regex commentPattern("//.*");

void removeComments(string& line) {
    line = regex_replace(line, commentPattern, "");
}

void stripNewlines(string& line) {
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
}

vector<string> splitString(string& line, const char separator) {
    vector<string> result;
    string current {""};

    for (size_t i = 0; i < line.length(); ++i) {
        if (line[i] == separator) {
            if (!current.empty()) {
                result.push_back(current);
                current = "";
            }
            continue;
        }
        current += line[i];
    }

    if (!current.empty()) {
        result.push_back(current);
    }

    return result;
}
