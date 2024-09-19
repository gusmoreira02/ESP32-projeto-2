# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Gustavo/esp/v5.2.2/esp-idf/components/bootloader/subproject"
  "C:/- Documentos/Desktop/Trab2/hello_world/build/bootloader"
  "C:/- Documentos/Desktop/Trab2/hello_world/build/bootloader-prefix"
  "C:/- Documentos/Desktop/Trab2/hello_world/build/bootloader-prefix/tmp"
  "C:/- Documentos/Desktop/Trab2/hello_world/build/bootloader-prefix/src/bootloader-stamp"
  "C:/- Documentos/Desktop/Trab2/hello_world/build/bootloader-prefix/src"
  "C:/- Documentos/Desktop/Trab2/hello_world/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/- Documentos/Desktop/Trab2/hello_world/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/- Documentos/Desktop/Trab2/hello_world/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
