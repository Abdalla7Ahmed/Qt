# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Bank_Management_System_autogen"
  "CMakeFiles/Bank_Management_System_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Bank_Management_System_autogen.dir/ParseCache.txt"
  )
endif()
