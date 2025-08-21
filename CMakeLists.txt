cmake_minimum_required(VERSION 3.14)

project(VMTranslator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

include_directories(include)

option(BUILD_TESTS "Build test binaries" OFF)

if(BUILD_TESTS)
    add_subdirectory(unit-test)
endif()

add_executable(VMTranslator
    src/CodeWriter.cpp
    src/main.cpp
    src/Parser.cpp
    src/utils.cpp
    src/VMConstants.cpp
    src/VMTranslator.cpp
)

set_target_properties(VMTranslator PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "v1.14.0"
)

FetchContent_MakeAvailable(googletest)
