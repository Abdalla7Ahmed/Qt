# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "9_Action_Menu_ToolBar_autogen"
  "CMakeFiles/9_Action_Menu_ToolBar_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/9_Action_Menu_ToolBar_autogen.dir/ParseCache.txt"
  )
endif()
