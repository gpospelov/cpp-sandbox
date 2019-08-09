cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(cpp-misc)

set(CMAKE_CXX_STANDARD 17)
find_package (Threads)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(CTest)

file(GLOB source_files "*.cpp")

foreach(src ${source_files})
  get_filename_component(base_name ${src} NAME_WE)
  file(GLOB include_files "*.cpp")
  add_executable(${base_name} ${src})
  add_test(${base_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${base_name})
  target_link_libraries(${base_name} pthread)
endforeach(src)
