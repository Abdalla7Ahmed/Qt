# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "11_ListWidget_autogen"
  "CMakeFiles/11_ListWidget_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/11_ListWidget_autogen.dir/ParseCache.txt"
  )
endif()
