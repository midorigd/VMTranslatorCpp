#include <gtest/gtest.h>
#include "utils.hpp"
#include "VMConstants.hpp"

#include <string>
#include <vector>
using namespace std;

TEST(utilsTest, splitTest1) {
    string str { "push constant 0" };
    vector<string> result { splitString(str) };

    EXPECT_EQ(result[0], "push");
    EXPECT_EQ(result[1], "constant");
    EXPECT_EQ(result[2], "0");
}

TEST(utilsTest, splitTest2) {
    string str { "if-goto LOOP" };
    vector<string> result { splitString(str) };

    EXPECT_EQ(result[0], "if-goto");
    EXPECT_EQ(result[1], "LOOP");
}

TEST(utilsTest, splitTest3) {
    string str { "sub" };
    vector<string> result { splitString(str) };

    EXPECT_EQ(result[0], "sub");
}

TEST(utilsTest, processTest) {
    EXPECT_EQ("string", processToString("string"));
    EXPECT_EQ("123", processToString(123));
    EXPECT_EQ("ARG", processToString(SEGMENT::ARG));
}
