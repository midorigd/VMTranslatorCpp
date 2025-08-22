#ifndef VMTRANSLATOR_H
#define VMTRANSLATOR_H

#include "CodeWriter.hpp"
#include "Parser.hpp"

#include "../build/_deps/googletest-src/googletest/include/gtest/gtest_prod.h"

#include <filesystem>
#include <string>
#include <vector>
using namespace std;

class VMTranslator {
public:
    VMTranslator(const string& sourceFile, bool commentMode);
    void translateAll();

private:
    vector<string> infiles;
    string outfile;
    CodeWriter codeWriter;

    static bool isSysFile(const string& vmFile);
    static bool sortSysInit(const string& file1, const string& file2);
    
    string fileManager(string file);
    void getVMFiles(const filesystem::path& dirname);
    void translate(const string& vmFile);

    FRIEND_TEST(VMTranslatorTest, fileManagerTest);
};

#endif
