#include <gtest/gtest.h>
#include "CodeWriter.hpp"
#include "utils.hpp"
#include "VMConstants.hpp"
#include "VMTranslator.hpp"

#include <iostream>
#include <filesystem>
#include <string>
using namespace std;

class VMTranslatorTest : public ::testing::Test {
protected:
    VMTranslator vm{"vmtest.txt", false};
};

TEST_F(VMTranslatorTest, fileManagerTest) {
    string filestr;
    do {
        cout << "Enter file path: ";
        cin >> filestr;

        filesystem::path file(filestr);
        filesystem::path dirname;

        if (filesystem::is_directory(file)) {
            dirname = file;
            cout << "file is directory: ";
        } else {
            dirname = file.parent_path();
            cout << "parent directory of file: ";
        }
        cout << dirname.string() << '\n';
        cout << "Basename: " + file.filename().string() + '\n';
        cout << "Extension: " + (file.has_extension() ? file.extension().string() : "NONE") + '\n';

    } while (filestr != "quit()");
}
