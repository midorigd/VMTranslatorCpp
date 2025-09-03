#ifndef VMCONSTANTS_H
#define VMCONSTANTS_H

#include <string>
#include <unordered_map>

namespace Translator {

/**
 * Enums for each VM command type.
 */
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

/**
 * Enums for each memory segment that can be accessed in VM commands.
 */
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

/**
 * Enums for each jump condition that can be written in assembly.
 */
enum class JUMP {
    JMP,
    JEQ,
    JLT,
    JGT,
    JNE
};

/**
 * Enums for each operation that can be performed in a VM arithmetic command.
 */
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

/**
 * Converts and returns the string form of a segment enum.
 */
std::string operator+(SEGMENT segment);

/**
 * Converts and returns the string form of a jump enum.
 */
std::string operator+(JUMP jump);

/**
 * Converts and returns the string form of an operator enum.
 */
std::string operator+(OP op);

/**
 * Converts and returns the jump enum equivalent of an operator enum.
 */
JUMP toJump(const OP& op);

/**
 * Returns whether or not the provided operator is a unary operator (- for neg, ~ for not).
 */
bool isUnaryOp(const OP& op);

/**
 * Returns whether or not the provided operator is a comparative logical operator (=, <, >).
 */
bool isLogicOp(const OP& op);

}

#endif
