#include "VMConstants.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

const unordered_map<SEGMENT, string> segmentToStr {
    {SEGMENT::SP, "SP"},
    {SEGMENT::LCL, "LCL"},
    {SEGMENT::ARG, "ARG"},
    {SEGMENT::THIS, "THIS"},
    {SEGMENT::THAT, "THAT"},
    {SEGMENT::CONSTANT, "constant"},
    {SEGMENT::STATIC, "static"},
    {SEGMENT::TEMP, "temp"},
    {SEGMENT::POINTER, "pointer"}
};

const unordered_map<JUMP, string> jumpToStr {
    {JUMP::JMP, "JMP"},
    {JUMP::JEQ, "JEQ"},
    {JUMP::JGT, "JGT"},
    {JUMP::JLT, "JLT"},
    {JUMP::JNE, "JNE"}
};

const unordered_map<OP, string> opToStr {
    {OP::ADD, "+"},
    {OP::SUB, "-"},
    {OP::AND, "&"},
    {OP::OR, "|"},
    {OP::EQ, +JUMP::JEQ},
    {OP::GT, +JUMP::JGT},
    {OP::LT, +JUMP::JLT},
    {OP::NEG, "-"},
    {OP::NOT, "!"}
};

const unordered_map<OP, JUMP> opToJump {
    {OP::EQ, JUMP::JEQ},
    {OP::GT, JUMP::JGT},
    {OP::LT, JUMP::JLT}
};

string operator+(SEGMENT segment) {
    return segmentToStr.at(segment);
}

string operator+(JUMP jump) {
    return jumpToStr.at(jump);
}

string operator+(OP op) {
    return opToStr.at(op);
}

JUMP toJump(const OP& op) {
    if (opToJump.find(op) != opToJump.end()) {
        return opToJump.at(op);
    } else {
        cerr << "Not a logic operator\n";
        exit(4);
    }
}

bool isUnaryOp(const OP& op) {
    return (op == OP::NOT || op == OP::NEG);
}

bool isLogicOp(const OP& op) {
    return opToJump.find(op) != opToJump.end();
}
