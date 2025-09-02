#ifndef CODEWRITER_H
#define CODEWRITER_H

#include "utils.hpp"
#include "VMConstants.hpp"

#include "../build/_deps/googletest-src/googletest/include/gtest/gtest_prod.h"

#include <fstream>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>

namespace Translator {

namespace fs = std::filesystem;

class CodeWriter {
public:
    CodeWriter(const fs::path& outfile, bool commentMode);
    void loadFile(const fs::path& vmFile);

    void writeBootstrap();
    void writeArithmetic(const OP& command);
    void writePushPop(const COMMAND& command, const SEGMENT& segment, const int index);
    void writeLabel(const std::string& label);
    void writeGoto(const std::string& label);
    void writeIf(const std::string& label);
    void writeCall(const std::string& functionName, const int nArgs);
    void writeFunction(const std::string& functionName, const int nVars);
    void writeReturn();

private:
    static const int STACK_POINTER;
    static const std::string INIT_FUNC;
    static const std::string TEMP_ADDR;
    static const std::string TEMP_VAR;
    static const std::string RET_ADDR;
    static const std::string END_FRAME;

    static const std::map<SEGMENT, int> mappedSegments;

    std::ofstream outfile;
    bool commentMode;

    int arithLabelID;
    int functionLabelID;
    int returnAddressID;
    std::stack<std::string> callStack;

    std::string filename;

    std::string currFunction() const;
    std::string createBoundLabel(const std::string& label) const;
    std::string createReturnLabel();
    std::pair<std::string, std::string> createUniqueLabels(int& counter, const std::string& category, const std::string& label1, const std::string& label2);
    std::pair<std::string, std::string> createLogicLabels();
    std::pair<std::string, std::string> createFunctionLabels();

    void writeCommand(const std::string& command);
    void writeComment(const std::string& comment);
    template <typename T>
    void commandA(const T& label);
    void commandC(const std::string& dest, const std::string& comp);
    void commandC(const std::string& comp, const JUMP& jump);
    void commandL(const std::string& label);

    void increment(const std::string& reg);
    void decrement(const std::string& reg);
    void memToData();
    void dataToMem();
    void dereferencePtr();
    void absJump();
    void loadArgPtr();
    void loadStackPtr();
    
    template <typename T>
    void constToData(const T& constant);
    template <typename T>
    void ptrToData(const T& pointer);
    template <typename T>
    void dataToPtr(const T& pointer);

    void push(const std::string& elem);
    void pushD();
    void popD();

    template <typename T>
    void savePointer(const T& pointer);
    template <typename T, typename U>
    void copyPointer(const T& src, const U& dest);
    template <typename T>
    void restorePointer(const T& pointer, const int offset);

    FRIEND_TEST(CodeWriterTest, boundLabelTest);
    FRIEND_TEST(CodeWriterTest, returnLabelTest);
    FRIEND_TEST(CodeWriterTest, basicsTest);
};

#include "CodeWriter.tpp"

}

#endif
