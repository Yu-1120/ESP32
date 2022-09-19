# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "AutoUploadGithub_autogen"
  "CMakeFiles\\AutoUploadGithub_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AutoUploadGithub_autogen.dir\\ParseCache.txt"
  )
endif()
