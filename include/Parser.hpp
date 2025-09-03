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
    /**
     * Creates a new Parser module to read and process VM commands from the given file.
     */
    Parser(const fs::path& filename);

    /**
     * Returns whether or not the parser has more lines to process in the file.
     */
    bool hasMoreLines();

    /**
     * Reads in the next VM command from input and splits it into its different parts if applicable.
     */
    void advance();

    /**
     * Returns the type of the current VM command.
     */
    COMMAND commandType() const;

    /**
     * Returns the first argument in the current VM command. Does not apply to return commands
     */
    template <typename T>
    T arg1() const;

    /**
     * Returns the second argument in the current VM command. Only applies to push/pop and function call/definition commands.
     */
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
