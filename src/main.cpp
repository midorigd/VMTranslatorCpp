#include "utils.hpp"
#include "VMTranslator.hpp"

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (!Translator::isValidArguments(argc, argv)) {
        Translator::displayUsage();
        exit(1);
    }

    string sourceFile { argv[1] };
    bool commentMode { argc == 3 };

    Translator::VMTranslator translator(sourceFile, commentMode);
    translator.translateAll();

    return 0;
}

/**
 * Exit codes:
 * 1: Incorrect argv usage
 * 2: File not opened
 * 3: Pop to constant segment
 * 4: Convert non-logic operator to JUMP
 * 5: Undefined type in processToString
 */
