# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "5_spaces_splitter_budy_tab_autogen"
  "CMakeFiles/5_spaces_splitter_budy_tab_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/5_spaces_splitter_budy_tab_autogen.dir/ParseCache.txt"
  )
endif()
