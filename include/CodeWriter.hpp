#ifndef CODEWRITER_H
#define CODEWRITER_H

#include "utils.hpp"
#include "VMConstants.hpp"

#include "../build/_deps/googletest-src/googletest/include/gtest/gtest_prod.h"
// #include <gtest/gtest_prod.h>

#include <array>
#include <fstream>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

class CodeWriter {
public:
    CodeWriter(const filesystem::path& outfile, bool commentMode);
    ~CodeWriter();
    void loadFile(const filesystem::path& vmFile);

    void writeBootstrap();
    void writeArithmetic(const OP& command);
    void writePushPop(const COMMAND& command, const SEGMENT& segment, const int index);
    void writeLabel(const string& label);
    void writeGoto(const string& label);
    void writeIf(const string& label);
    void writeCall(const string& functionName, const int nArgs);
    void writeFunction(const string& functionName, const int nVars);
    void writeReturn();

private:
    static const int STACK_POINTER;
    static const string INIT_FUNC;
    static const string TEMP_ADDR;
    static const string TEMP_VAR;
    static const string RET_ADDR;
    static const string END_FRAME;

    static const map<SEGMENT, int> mappedSegments;

    ofstream outfile;
    bool commentMode;

    int arithLabelID;
    int functionLabelID;
    int returnAddressID;
    stack<string> callStack;

    string filename;

    string currFunction() const;
    string createBoundLabel(const string& label) const;
    string createReturnLabel();
    array<string, 2> createUniqueLabels(int& counter, const string& category, const string& label1, const string& label2);
    array<string, 2> createLogicLabels();
    array<string, 2> createFunctionLabels();

    void writeCommand(const string& command);
    void writeComment(const string& comment);
    template <typename T>
    void commandA(const T& label);
    void commandC(const string& dest, const string& comp);
    void commandC(const string& comp, const JUMP& jump);
    void commandL(const string& label);

    void increment(const string& reg);
    void decrement(const string& reg);
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

    void push(const string& elem);
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

#endif
