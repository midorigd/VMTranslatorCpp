include(GoogleTest)

add_executable(utilsTest
    utilsTest.cpp
    ../src/utils.cpp
    ../src/VMConstants.cpp
)

target_link_libraries(utilsTest
    gtest_main
    pthread
)

add_executable(CodeWriterTest
    CodeWriterTest.cpp
    ../src/CodeWriter.cpp
    ../src/utils.cpp
    ../src/VMConstants.cpp
)

target_link_libraries(CodeWriterTest
    gtest_main
    pthread
)

add_executable(VMTranslatorTest
    VMTranslatorTest.cpp
    ../src/CodeWriter.cpp
    ../src/Parser.cpp
    ../src/utils.cpp
    ../src/VMConstants.cpp
    ../src/VMTranslator.cpp
)

target_link_libraries(VMTranslatorTest
    gtest_main
    pthread
)

# add_test(NAME utils COMMAND utilsTest)
gtest_discover_tests(utilsTest)
gtest_discover_tests(CodeWriterTest)
gtest_discover_tests(VMTranslatorTest)
