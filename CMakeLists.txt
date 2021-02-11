cmake_minimum_required(VERSION 3.17)
project(lois2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

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

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(test gtest gtest_main)