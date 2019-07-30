cmake_minimum_required(VERSION 3.5)
project(global_fancy_example VERSION 0.0.1 LANGUAGES CXX)

add_executable(global_fancy_example main.cpp)

find_package(FancyLib 1.0 REQUIRED)
target_link_libraries(global_fancy_example FancyLib::FancyLib)
