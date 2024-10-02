# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "6_Login_App_autogen"
  "CMakeFiles/6_Login_App_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/6_Login_App_autogen.dir/ParseCache.txt"
  )
endif()
