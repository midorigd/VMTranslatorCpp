#include "VMTranslator.hpp"
#include "CodeWriter.hpp"
#include "Parser.hpp"
#include "VMConstants.hpp"

#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>
using namespace std;

VMTranslator::VMTranslator(const string& sourceFile, bool commentMode) :
    outfile(fileManager(sourceFile)),
    codeWriter(outfile, commentMode) {}

void VMTranslator::translateAll() {
    if (isSysFile(infiles[0])) {
        codeWriter.writeBootstrap();
    }

    for (const filesystem::path& vmFile : infiles) {
        translate(vmFile);
    }
}

bool VMTranslator::isSysFile(const filesystem::path& vmFile) {
    string SYS_FUNC { "Sys.vm" };
    return vmFile.filename() == SYS_FUNC;
}

bool VMTranslator::sortSysInit(const filesystem::path& file1, const filesystem::path& file2) {
    if (isSysFile(file1)) {
        return true;
    } else if (isSysFile(file2)) {
        return false;
    } else {
        return file1 < file2;
    }
}

filesystem::path VMTranslator::fileManager(string file) {
    while (!file.empty() && (file.back() == filesystem::path::preferred_separator)) {
        file.pop_back();
    }

    filesystem::path filepath(file);
    filesystem::path dirname(filepath.parent_path());

    if (filepath.has_extension()) {
        infiles.push_back(filepath);
    } else {
        dirname /= filepath.filename();
        getVMFiles(dirname);
        sort(infiles.begin(), infiles.end(), sortSysInit);
    }

    outfile = dirname / filepath.filename().replace_extension(".asm");
    return outfile;
}

void VMTranslator::getVMFiles(const filesystem::path& dirname) {
    for (const filesystem::directory_entry& file : filesystem::directory_iterator(dirname)) {
        if (file.is_regular_file() && file.path().extension() == ".vm") {
            infiles.push_back(file.path());
        }
    }
}

void VMTranslator::translate(const filesystem::path& vmFile) {
    Parser parser(vmFile);
    codeWriter.loadFile(filesystem::path(vmFile).stem());

    while (parser.hasMoreLines()) {
        parser.advance();

        switch (parser.commandType()) {
            case COMMAND::ARITHMETIC:
                codeWriter.writeArithmetic(parser.arg1<OP>());
                break;
            case COMMAND::LABEL:
                codeWriter.writeLabel(parser.arg1<string>());
                break;
            case COMMAND::GOTO:
                codeWriter.writeGoto(parser.arg1<string>());
                break;
            case COMMAND::IF:
                codeWriter.writeIf(parser.arg1<string>());
                break;
            case COMMAND::CALL:
                codeWriter.writeCall(parser.arg1<string>(), parser.arg2());
                break;
            case COMMAND::FUNCTION:
                codeWriter.writeFunction(parser.arg1<string>(), parser.arg2());
                break;
            case COMMAND::RETURN:
                codeWriter.writeReturn();
                break;
            default:
                codeWriter.writePushPop(parser.commandType(), parser.arg1<SEGMENT>(), parser.arg2());
                break;
        }
    }
}
