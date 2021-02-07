cmake_minimum_required(VERSION 3.17)
project(lois2)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE
        Validation.h
        Validation.cpp
        Unpossible.h
        Unpossible.cpp
        )

set(TESTS
        tests/testValidation.cpp
        tests/testUnpossible.cpp
        )

add_executable(lois2 main.cpp ${SOURCE})
add_executable(test ${SOURCE} ${TESTS})

target_link_libraries(test gtest gtest_main)