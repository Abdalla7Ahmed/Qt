# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "14_QFileDialog_autogen"
  "CMakeFiles/14_QFileDialog_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/14_QFileDialog_autogen.dir/ParseCache.txt"
  )
endif()
