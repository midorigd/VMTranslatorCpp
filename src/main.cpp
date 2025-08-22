#include "VMTranslator.hpp"

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3 || argc == 3 && string(argv[2]) != "-c"s) {
        cerr << "Usage: bin/VMTranslator <dirname OR filename.vm> [-c]\n";
        cerr << "   -c: Enables comments in output file\n";
        exit(1);
    }

    string sourceFile { argv[1] };

    VMTranslator translator(sourceFile, argc == 3);
    translator.translateAll();

    return 0;
}

/**
 * Exit codes:
 * 1: Incorrect argv usage
 * 2: File not found
 * 3: Pop to constant segment
 * 4: Convert non-logic operator to JUMP
 * 5: Undefined type in processToString
 */
