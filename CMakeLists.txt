cmake_minimum_required(VERSION 2.8.9)
project(rbtree)

#set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14 -g")
#headers
include_directories(include)
#include_directories(lib)
find_package (Threads REQUIRED)

#set global var SOURCE with all source file names
file(GLOB SOURCES "src/*.cpp")

add_executable(rbtree ${SOURCES})

target_link_libraries(rbtree gtest pthread)
