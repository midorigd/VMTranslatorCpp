#include "Parser.hpp"
#include "utils.hpp"
#include "VMConstants.hpp"

namespace Translator {

using namespace std;

const regex Parser::commentPattern("//.*");

const unordered_map<string, COMMAND> Parser::commandLookup {
    {"push", COMMAND::PUSH},
    {"pop", COMMAND::POP},
    {"label", COMMAND::LABEL},
    {"goto", COMMAND::GOTO},
    {"if-goto", COMMAND::IF},
    {"call", COMMAND::CALL},
    {"function", COMMAND::FUNCTION},
    {"return", COMMAND::RETURN},
    {"arithmetic", COMMAND::ARITHMETIC}
};

const unordered_map<string, OP> Parser::opLookup {
    {"add", OP::ADD},
    {"sub", OP::SUB},
    {"and", OP::AND},
    {"or", OP::OR},
    {"eq", OP::EQ},
    {"gt", OP::GT},
    {"lt", OP::LT},
    {"neg", OP::NEG},
    {"not", OP::NOT}
};

const unordered_map<string, SEGMENT> Parser::segmentLookup {
    {"SP", SEGMENT::SP},
    {"local", SEGMENT::LCL},
    {"argument", SEGMENT::ARG},
    {"this", SEGMENT::THIS},
    {"that", SEGMENT::THAT},
    {"constant", SEGMENT::CONSTANT},
    {"static", SEGMENT::STATIC},
    {"temp", SEGMENT::TEMP},
    {"pointer", SEGMENT::POINTER}
};

Parser::Parser(const filesystem::path& filename) : infile(filename) {
    if (!infile) {
        cerr << "Input file not opened\n";
        exit(2);
    }
}

Parser::~Parser() {
    infile.close();
}

bool Parser::hasMoreLines() {
    return infile.peek() != EOF;
}

void Parser::advance() {
    while (hasMoreLines()) {
        string line;

        getline(infile >> ws, line);
        removeComments(line);
        stripNewlines(line);

        if (!line.empty()) {
            current = splitString(line);
            return;
        }
    }
}

COMMAND Parser::commandType() const {
    if (commandLookup.find(current[0]) != commandLookup.end()) {
        return commandLookup.at(current[0]);
    } else {
        return COMMAND::ARITHMETIC;
    }
}

int Parser::arg2() const {
    return stoi(current[2]);
}

}
