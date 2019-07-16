set(test unittests)

include(GoogleTest)

file(GLOB source_files "src/*.cpp")
file(GLOB include_files "src/*.h")

add_executable(${test} ${source_files} ${include_files})
target_link_libraries(${test} gtest_main)

if (FANCYLIB_TESTS_AUTOEXEC)
    if (FANCYLIB_TESTS_AUTODISCOVERY)
        gtest_discover_tests(${test})
    else()
        add_custom_target(${test}_run ALL DEPENDS ${test} COMMAND ${test})
    endif()
endif()


