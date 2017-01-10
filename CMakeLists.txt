cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(CTest)
add_subdirectory(cppmisc)


