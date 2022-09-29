# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/11868/esp/esp-idf/components/bootloader/subproject"
  "E:/GitHub/ESP32/ESP32-IDF/hello_world/build/bootloader"
  "E:/GitHub/ESP32/ESP32-IDF/hello_world/build/bootloader-prefix"
  "E:/GitHub/ESP32/ESP32-IDF/hello_world/build/bootloader-prefix/tmp"
  "E:/GitHub/ESP32/ESP32-IDF/hello_world/build/bootloader-prefix/src/bootloader-stamp"
  "E:/GitHub/ESP32/ESP32-IDF/hello_world/build/bootloader-prefix/src"
  "E:/GitHub/ESP32/ESP32-IDF/hello_world/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/GitHub/ESP32/ESP32-IDF/hello_world/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/GitHub/ESP32/ESP32-IDF/hello_world/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
