set(library_name fancylib)

file(GLOB_RECURSE source_list "*.cpp" "*.h")

add_library(${library_name} SHARED ${source_list})

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/core
)

target_link_libraries(${library_name} Qt5::Widgets)
