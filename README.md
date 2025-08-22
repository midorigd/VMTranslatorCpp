# VMTranslator (C++)

This is a C++ implementation of the VM language to Hack assembly translator from projects 7-8 of nand2tetris.

The assembler takes a single `.vm` file or a directory of `.vm` files as a command-line argument and creates an `.asm` file with the corresponding assembly code.

## Modules

CodeWriter: Writes assembly commands to output  
Parser: Handles input filestream, processes commands and arguments  
VMConstants: Enums and processing functions for commands, segments, and operators  
VMTranslator: Drives the translation process  
main: Program entry point  
utils: Helper functions for string and command line argument processing

## Building the project

Run the following from the terminal:

```zsh
git clone https://github.com/midorigd/VMTranslatorCpp
cd VMTranslatorCpp
mkdir build
cd build
cmake ..
make
```

## Running the project

Run the following from the build directory:

```zsh
bin/VMTranslator <dirname OR filename.vm> [-c]
```

### Flags

`-c`: Enables comments in output file

## Notes

My Python implementation of this project: [VMTranslator (Python)](https://github.com/midorigd/VMTranslatorPython)

## References

[nand2tetris](https://www.nand2tetris.org/course)

