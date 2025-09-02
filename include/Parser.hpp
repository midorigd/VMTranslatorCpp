#ifndef PARSER_H
#define PARSER_H

#include "VMConstants.hpp"

#include <filesystem>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

namespace Translator {

namespace fs = std::filesystem;

class Parser {
public:
    Parser(const fs::path& filename);
    bool hasMoreLines();
    void advance();
    COMMAND commandType() const;
    template <typename T>
    T arg1() const;
    int arg2() const;

private:
    static const std::regex commentPattern;
    static const std::unordered_map<std::string, COMMAND> commandLookup;
    static const std::unordered_map<std::string, OP> opLookup;
    static const std::unordered_map<std::string, SEGMENT> segmentLookup;

    std::ifstream infile;
    std::vector<std::string> current;
};

#include "Parser.tpp"

}

#endif
