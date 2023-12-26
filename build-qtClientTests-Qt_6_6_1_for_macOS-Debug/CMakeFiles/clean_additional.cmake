# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/clientQtTests_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/clientQtTests_autogen.dir/ParseCache.txt"
  "clientQtTests_autogen"
  )
endif()
