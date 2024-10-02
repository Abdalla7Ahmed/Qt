# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Online_Shopping_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Online_Shopping_autogen.dir/ParseCache.txt"
  "Online_Shopping_autogen"
  )
endif()
