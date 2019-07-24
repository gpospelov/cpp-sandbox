if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_VARIADIC_MAX=10 /wd4100 /wd4275")
endif()

option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)

option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)
add_subdirectory(googletest)
