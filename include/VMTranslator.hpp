#ifndef VMTRANSLATOR_H
#define VMTRANSLATOR_H

#include "CodeWriter.hpp"
#include "Parser.hpp"

#include "../build/_deps/googletest-src/googletest/include/gtest/gtest_prod.h"

#include <filesystem>
#include <string>
#include <vector>

namespace Translator {

namespace fs = std::filesystem;

class VMTranslator {
public:
    VMTranslator(const std::string& sourceFile, bool commentMode);
    void translateAll();

private:
    std::vector<fs::path> infiles;
    fs::path outfile;
    CodeWriter codeWriter;

    static bool isSysFile(const fs::path& vmFile);
    static bool sortSysInit(const fs::path& file1, const fs::path& file2);

    fs::path fileManager(std::string file);
    void getVMFiles(const fs::path& dirname);
    void translate(const fs::path& vmFile);
};

}

#endif
