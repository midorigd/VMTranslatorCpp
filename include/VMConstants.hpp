#ifndef VMCONSTANTS_H
#define VMCONSTANTS_H

#include <string>
#include <unordered_map>

namespace Translator {

enum class COMMAND {
    PUSH,
    POP,
    LABEL,
    GOTO,
    IF,
    CALL,
    FUNCTION,
    RETURN,
    ARITHMETIC
};

enum class SEGMENT {
    SP,
    LCL,
    ARG,
    THIS,
    THAT,
    CONSTANT,
    STATIC,
    TEMP,
    POINTER
};

enum class JUMP {
    JMP,
    JEQ,
    JLT,
    JGT,
    JNE
};

enum class OP {
    ADD,
    SUB,
    AND,
    OR,
    EQ,
    GT,
    LT,
    NEG,
    NOT
};

extern const std::unordered_map<SEGMENT, std::string> segmentToStr;
extern const std::unordered_map<JUMP, std::string> jumpToStr;
extern const std::unordered_map<OP, std::string> opToStr;
extern const std::unordered_map<OP, JUMP> opToJump;

std::string operator+(SEGMENT segment);
std::string operator+(JUMP jump);
std::string operator+(OP op);
JUMP toJump(const OP& op);

bool isUnaryOp(const OP& op);
bool isLogicOp(const OP& op);

}

#endif
