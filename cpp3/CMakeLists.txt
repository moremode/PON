cmake_minimum_required(VERSION 2.6)

project(cpp3)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(cpp3 main.cpp)
add_executable(test test.cpp)

add_subdirectory(lib)

target_link_libraries(cpp3 cpp3lib)
target_link_libraries(test cpp3lib)
target_link_libraries(test ${GTEST_LIBRARIES} pthread)
