#include "CodeWriter.hpp"
#include "utils.hpp"
#include "VMConstants.hpp"

#include <array>
#include <iostream>
#include <map>
#include <string>
using namespace std;

const int CodeWriter::STACK_POINTER = 256;
const string CodeWriter::INIT_FUNC = "Sys.init";
const string CodeWriter::TEMP_ADDR = "addr";
const string CodeWriter::TEMP_VAR = "y";
const string CodeWriter::RET_ADDR = "retAddr";
const string CodeWriter::END_FRAME = "endFrame";

const map<SEGMENT, int> CodeWriter::mappedSegments {
    {SEGMENT::LCL, 4},
    {SEGMENT::ARG, 3},
    {SEGMENT::THIS, 2},
    {SEGMENT::THAT, 1},
};


CodeWriter::CodeWriter(const string& outfile, bool commentMode) :
    outfile(outfile),
    commentMode(commentMode),
    arithLabelID(0),
    functionLabelID(0),
    returnAddressID(0)
    { callStack.push(""); }

CodeWriter::~CodeWriter() {
    outfile.close();
}

void CodeWriter::loadFile(const string& vmFile) {
    filename = vmFile;
}

void CodeWriter::writeBootstrap() {
    writeComment("Bootstrap code");

    callStack.push(INIT_FUNC);

    constToData(STACK_POINTER);
    dataToPtr(SEGMENT::SP);
    writeCall(INIT_FUNC, 0);
}

void CodeWriter::writeArithmetic(const OP& command) {
    writeComment(+command);

    if (isUnaryOp(command)) {
        popD();
        commandC("D", +command + "D");
        pushD();

    } else if (isLogicOp(command)) {
        array<string, 2> labels { createLogicLabels() };
        string trueLabel { labels[0] };
        string falseLabel { labels[1] };

        popD();
        dataToPtr(TEMP_VAR);

        popD();
        commandA(TEMP_VAR);
        commandC("D", "D-M");

        commandA(trueLabel);
        commandC("D", toJump(command));

        commandC("D", "0"); // why tf does this work as an int
        commandA(falseLabel);
        absJump();

        commandL(trueLabel);
        commandC("D", "-1");

        commandL(falseLabel);
        pushD();
        
    } else {
        popD();
        dataToPtr(TEMP_VAR);

        popD();
        commandA(TEMP_VAR);
        commandC("D", "D" + +command + "M");
        pushD();
    }
}

void CodeWriter::writePushPop(const COMMAND& command, const SEGMENT& segment, const int index) {
    writeComment((command == COMMAND::PUSH ? "push " : "pop ") + +segment + " " + to_string(index));

    if (segment == SEGMENT::CONSTANT) {
        if (command == COMMAND::POP) {
            cerr << "Cannot pop to constant segment\n";
            exit(3);
        }
        constToData(index);
        pushD();

    } else if (mappedSegments.find(segment) != mappedSegments.end()) {
        copyPointer(segment, TEMP_ADDR);
        
        constToData(index);
        commandA(TEMP_ADDR);
        commandC("M", "M+D");

        if (command == COMMAND::PUSH) {
            dereferencePtr();
            memToData();
            pushD();
        } else {
            popD();
            commandA(TEMP_ADDR);
            dereferencePtr();
            dataToMem();
        }

    } else {
        string pointer;
        switch (segment) {
            case SEGMENT::STATIC:
                pointer = filename + "." + to_string(index);
                break;
            case SEGMENT::TEMP:
                pointer = to_string(index + 5);
                break;
            case SEGMENT::POINTER:
                pointer = (index == 0) ? +SEGMENT::THIS : +SEGMENT::THAT;
                break;
        }

        if (command == COMMAND::PUSH) {
            ptrToData(pointer);
            pushD();
        } else {
            popD();
            dataToPtr(pointer);
        }
    }
}

void CodeWriter::writeLabel(const string& label) {
    writeComment("label " + label);
    commandL(createBoundLabel(label));
}

void CodeWriter::writeGoto(const string& label) {
    writeComment("goto " + label);
    commandA(createBoundLabel(label));
    absJump();
}

void CodeWriter::writeIf(const string& label) {
    writeComment("if-goto " + label);
    popD();
    commandA(createBoundLabel(label));
    commandC("D", JUMP::JNE);
}

void CodeWriter::writeCall(const string& functionName, const int nArgs) {
    writeComment("call " + functionName + " " + to_string(nArgs));

    string returnLabel { createReturnLabel() };

    constToData(returnLabel);
    pushD();
    
    for (const pair<const SEGMENT, const int>& pair : mappedSegments) {
        savePointer(pair.first);
    }

    ptrToData(SEGMENT::SP);
    commandA(5 + nArgs);
    commandC("D", "D-A");

    dataToPtr(SEGMENT::ARG);

    copyPointer(SEGMENT::SP, SEGMENT::LCL);

    commandA(functionName);
    absJump();

    commandL(returnLabel);
}

void CodeWriter::writeFunction(const string& functionName, const int nVars) {
    writeComment("function " + functionName + " " + to_string(nVars));

    array<string, 2> labels { createFunctionLabels() };
    string loopLabel { labels[0] };
    string endLabel { labels[1] };

    commandL(functionName);
    constToData(nVars);

    commandL(loopLabel);
    commandA(endLabel);
    commandC("D", JUMP::JEQ);

    push("0");
    decrement("D");

    commandA(loopLabel);
    absJump();

    commandL(endLabel);

    callStack.push(functionName);
}

void CodeWriter::writeReturn() {
    writeComment("return");

    copyPointer(SEGMENT::LCL, END_FRAME);
    restorePointer(RET_ADDR, 5);

    popD();
    loadArgPtr();
    dereferencePtr();
    dataToMem();

    ptrToData(SEGMENT::ARG);
    loadStackPtr();
    commandC("M", "D+1");

    for (const pair<const SEGMENT, const int>& pair : mappedSegments) {
        restorePointer(pair.first, pair.second);
    }

    commandA(RET_ADDR);
    dereferencePtr();
    absJump();
}

string CodeWriter::currFunction() const {
    return callStack.top();
}

string CodeWriter::createBoundLabel(const string& label) const {
    return currFunction() + "$" + label;
}

string CodeWriter::createReturnLabel() {
    return currFunction() + "$ret." + to_string(returnAddressID++);
}

array<string, 2> CodeWriter::createUniqueLabels(int& counter, const string& category, const string& label1, const string& label2) {
    string id { to_string(counter++) };
    return {category + "." + label1 + id, category + "." + label2 + id};
}

array<string, 2> CodeWriter::createLogicLabels() {
    return createUniqueLabels(arithLabelID, "LOGIC", "COMPTRUE", "COMPEND");
}

array<string, 2> CodeWriter::createFunctionLabels() {
    return createUniqueLabels(functionLabelID, "FUNC", "INITLOCALVARS", "INITLOCALSEND");
}

void CodeWriter::writeCommand(const string& command) {
    outfile << command << '\n';
}

void CodeWriter::writeComment(const string& comment) {
    if (commentMode) {
        writeCommand("// " + comment);
    }
}

void CodeWriter::commandC(const string& dest, const string& comp) {
    writeCommand(dest + "=" + comp);
}

void CodeWriter::commandC(const string& comp, const JUMP& jump) {
    writeCommand(comp + ";" + +jump);
}

void CodeWriter::commandL(const string& label) {
    writeCommand("(" + label + ")");
}

void CodeWriter::increment(const string& reg) {
    commandC(reg, reg + "+1");
}

void CodeWriter::decrement(const string& reg) {
    commandC(reg, reg + "-1");
}

void CodeWriter::memToData() {
    commandC("D", "M");
}

void CodeWriter::dataToMem() {
    commandC("M", "D");
}

void CodeWriter::dereferencePtr() {
    commandC("A", "M");
}

void CodeWriter::absJump() {
    commandC("0", JUMP::JMP);
}

void CodeWriter::loadArgPtr() {
    commandA(SEGMENT::ARG);
}

void CodeWriter::loadStackPtr() {
    commandA(SEGMENT::SP);
}

void CodeWriter::push(const string& elem) {
    loadStackPtr();
    dereferencePtr();
    commandC("M", elem);
    loadStackPtr();
    increment("M");
}

void CodeWriter::pushD() {
    push("D");
}

void CodeWriter::popD() {
    loadStackPtr();
    commandC("AM", "M-1");
    memToData();
}
