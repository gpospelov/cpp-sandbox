cmake_minimum_required(VERSION 3.5)
project(fancylib VERSION 1.0.0 LANGUAGES CXX)

option(FANCYLIB_TESTS_AUTOEXEC "Execute tests automatically at the end of the build" ON)
option(FANCYLIB_TESTS_AUTODISCOVERY "Auto discover tests and add to ctest" ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(CTest)
include(configuration)

add_subdirectory(src)
add_subdirectory(thirdparty/gtest)
add_subdirectory(tests)
add_subdirectory(example)
