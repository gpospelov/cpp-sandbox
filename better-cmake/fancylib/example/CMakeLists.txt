add_executable(example main.cpp)

find_package(FancyLib 1.0 REQUIRED)
target_link_libraries(example FancyLib::FancyLib)
