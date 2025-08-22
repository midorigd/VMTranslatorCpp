#ifndef PARSER_H
#define PARSER_H

#include "VMConstants.hpp"

#include <filesystem>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Parser {
public:
    Parser(const filesystem::path& filename);
    ~Parser();
    bool hasMoreLines();
    void advance();
    COMMAND commandType() const;
    template <typename T>
    T arg1() const;
    int arg2() const;

private:
    static const regex commentPattern;
    static const unordered_map<string, COMMAND> commandLookup;
    static const unordered_map<string, OP> opLookup;
    static const unordered_map<string, SEGMENT> segmentLookup;

    ifstream infile;
    vector<string> current;
};

#include "Parser.tpp"

#endif
