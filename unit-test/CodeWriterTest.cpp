// #include "../build/_deps/googletest-src/googletest/include/gtest/gtest.h"
#include <gtest/gtest.h>
#include "CodeWriter.hpp"

#include <string>
using namespace std;

class CodeWriterTest : public ::testing::Test {
protected:
    CodeWriter writer{"testfile.asm", false};
};

TEST_F(CodeWriterTest, boundLabelTest) {
    writer.callStack.push("funcName");
    EXPECT_EQ(writer.createBoundLabel("LOOP"), "funcName$LOOP");
}

TEST_F(CodeWriterTest, returnLabelTest) {
    writer.callStack.push("funcName");
    EXPECT_EQ(writer.createReturnLabel(), "funcName$ret.0");
}

TEST_F(CodeWriterTest, basicsTest) {
    writer.writeBootstrap();

    writer.commandA(2);
    writer.commandA("LOOP");
    writer.commandA(SEGMENT::SP);

    writer.commandC("D", "D+M");
    writer.commandC("0", JUMP::JMP);
}
