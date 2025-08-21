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

    for (const string& vmFile : infiles) {
        translate(vmFile);
    }
}

bool VMTranslator::isSysFile(const string& vmFile) {
    string SYS_FUNC { "Sys.vm" };
    size_t sysLen { SYS_FUNC.length() };

    return !vmFile.compare(vmFile.length() - sysLen, sysLen, SYS_FUNC);
}

bool VMTranslator::sortSysInit(const string& file1, const string& file2) {
    if (isSysFile(file1)) {
        return true;
    } else if (isSysFile(file2)) {
        return false;
    } else {
        return file1 < file2;
    }
}

string VMTranslator::fileManager(string file) {
    while (!file.empty() && (file.back() == filesystem::path::preferred_separator)) {
        file.pop_back();
    }

    filesystem::path filepath(file);
    filesystem::path dirname(filepath.parent_path());

    if (filepath.has_extension()) {
        infiles.push_back(filepath.string());
    } else {
        dirname /= filepath.filename();
        getVMFiles(dirname);
        sort(infiles.begin(), infiles.end(), sortSysInit);
    }

    outfile = (dirname / filepath.filename().replace_extension(".asm")).string();
    return outfile;
}

void VMTranslator::getVMFiles(const filesystem::path& dirname) {
    for (const filesystem::directory_entry& file : filesystem::directory_iterator(dirname)) {
        if (file.is_regular_file() && file.path().extension() == ".vm") {
            infiles.push_back(file.path().string());
        }
    }
}

void VMTranslator::translate(const string& vmFile) {
    Parser parser(vmFile);
    codeWriter.loadFile(filesystem::path(vmFile).stem().string());

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
