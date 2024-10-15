cmake_minimum_required(VERSION 3.15...3.30)

project(Monkey VERSION 1.0
        DESCRIPTION "A Monkey implementation in C++"
        LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable compile_commands.json generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(SOURCES
        src/lexer.cc
        src/main.cc
        src/repl.cc
        src/token.cc
        src/ast.cc
        include/parser.h
        src/parser.cc
)

add_library(monkey SHARED ${SOURCES})
target_include_directories(monkey PUBLIC ${CMAKE_HOME_DIRECTORY}/include)



include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(basic_test
        test/basic.cc
        test/lexer_test.cc
        test/parser_test.cc
        test/test_utils.h)

target_link_libraries(basic_test monkey gtest gmock)

include(GoogleTest)
gtest_discover_tests(basic_test)