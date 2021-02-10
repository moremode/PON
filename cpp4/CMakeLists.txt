cmake_minimum_required(VERSION 2.6)

project(cpp4)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(cpp4 main.cpp)

add_subdirectory(lib)

target_link_libraries(cpp4 cpp4lib)