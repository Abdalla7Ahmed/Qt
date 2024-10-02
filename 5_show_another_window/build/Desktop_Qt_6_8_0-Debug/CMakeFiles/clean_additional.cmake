# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/show_another_window_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/show_another_window_autogen.dir/ParseCache.txt"
  "show_another_window_autogen"
  )
endif()
