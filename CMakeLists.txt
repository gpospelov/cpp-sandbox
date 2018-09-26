cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(cpp-misc)

set(CMAKE_CXX_STANDARD 14)
find_package (Threads)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(CTest)
add_subdirectory(cppmisc)


