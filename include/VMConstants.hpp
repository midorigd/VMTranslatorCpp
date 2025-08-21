#ifndef VMCONSTANTS_H
#define VMCONSTANTS_H

#include <string>
#include <unordered_map>
using namespace std;


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

extern const unordered_map<SEGMENT, string> segmentToStr;
extern const unordered_map<JUMP, string> jumpToStr;
extern const unordered_map<OP, string> opToStr;
extern const unordered_map<OP, JUMP> opToJump;

string operator+(SEGMENT segment);
string operator+(JUMP jump);
string operator+(OP op);
JUMP toJump(const OP& op);

bool isUnaryOp(const OP& op);
bool isLogicOp(const OP& op);

#endif
