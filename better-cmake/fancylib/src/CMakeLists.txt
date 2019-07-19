set(library_name fancylib)

file(GLOB_RECURSE source_list "*.cpp" "*.h")

add_library(${library_name} SHARED ${source_list})

# Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(FancyLib::FancyLib ALIAS ${library_name})

target_include_directories(${library_name}
    PUBLIC
        $<INSTALL_INTERFACE:public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core>
#    PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}/core
)

target_link_libraries(${library_name}
    PUBLIC
        Qt5::Widgets
    PRIVATE
        Boost::boost
)

# --- Installation instructions -----

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/FancyLib)

install(TARGETS ${library_name}
    EXPORT ${library_name}-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# This is required so that the exported target has the name FancyLib and not fancylib
set_target_properties(${library_name} PROPERTIES EXPORT_NAME FancyLib)

install(DIRECTORY public/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT ${library_name}-targets
  FILE
    FancyLibTargets.cmake
  NAMESPACE
    FancyLib::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/FancyLibConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/../cmake/FancyLibConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/FancyLibConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/FancyLibConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/FancyLibConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
export(EXPORT ${library_name}-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/FancyLibTargets.cmake NAMESPACE FancyLib::)

#Register package in user's package registry
export(PACKAGE FancyLib)
