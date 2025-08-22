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
    vector<filesystem::path> infiles;
    filesystem::path outfile;
    CodeWriter codeWriter;

    static bool isSysFile(const filesystem::path& vmFile);
    static bool sortSysInit(const filesystem::path& file1, const filesystem::path& file2);

    filesystem::path fileManager(string file);
    void getVMFiles(const filesystem::path& dirname);
    void translate(const filesystem::path& vmFile);

    // FRIEND_TEST(VMTranslatorTest, fileManagerTest);
};

#endif
