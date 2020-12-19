cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(libpon.so)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(cpp2 main.cpp)

target_link_libraries(cpp2 ${CMAKE_BINARY_DIR}/libpon.so)
target_link_libraries(cpp2 ${GTEST_LIBRARIES} pthread)
