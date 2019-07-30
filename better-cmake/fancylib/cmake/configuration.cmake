set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Boost 1.55 REQUIRED)

get_target_property(Qt5Widgets_location Qt5::Widgets LOCATION_Release)
message(STATUS "  ${Qt5Widgets_LIBRARIES} ${Qt5Widgets_location}")
message(STATUS "  Includes: ${Qt5Widgets_INCLUDE_DIRS}")
