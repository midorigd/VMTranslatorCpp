#include "utils.hpp"

#include <regex>

namespace Translator {

using namespace std;

bool isValidArguments(const int argc, const char* const argv[]) {
    return argc == 2 || (argc == 3 && string(argv[2]) == "-c"s);
}

void displayUsage() {
    cerr << "Usage: bin/VMTranslator <dirname OR filename.vm> [-c]\n";
    cerr << "   -c: Enables comments in output file\n";
}

void removeComments(string& line) {
    regex commentPattern("//.*");
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

}
