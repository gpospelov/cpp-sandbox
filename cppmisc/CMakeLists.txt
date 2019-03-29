file(GLOB source_files "*.cpp")

foreach(src ${source_files})
  get_filename_component(base_name ${src} NAME_WE)
  file(GLOB include_files "*.cpp")
  add_executable(${base_name} ${src})
  add_test(${base_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${base_name})
  target_link_libraries(${base_name} pthread)
endforeach(src)
