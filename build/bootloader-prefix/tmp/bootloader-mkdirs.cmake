# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/simeon/esp/esp-idf/components/bootloader/subproject"
  "/Users/simeon/Desktop/Repositories/ot_cli/build/bootloader"
  "/Users/simeon/Desktop/Repositories/ot_cli/build/bootloader-prefix"
  "/Users/simeon/Desktop/Repositories/ot_cli/build/bootloader-prefix/tmp"
  "/Users/simeon/Desktop/Repositories/ot_cli/build/bootloader-prefix/src/bootloader-stamp"
  "/Users/simeon/Desktop/Repositories/ot_cli/build/bootloader-prefix/src"
  "/Users/simeon/Desktop/Repositories/ot_cli/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/simeon/Desktop/Repositories/ot_cli/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/simeon/Desktop/Repositories/ot_cli/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
