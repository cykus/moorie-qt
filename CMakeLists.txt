project(MOORIE)
cmake_minimum_required(VERSION 2.6)

option(ENABLE_GUI "Kompilacja wraz z Qmoorie")

add_subdirectory(src)

message(STATUS)
message(STATUS "ENABLE_GUI = ${ENABLE_GUI}")
message(STATUS)

set(ENABLE_GUI ${ENABLE_GUI} CACHE BOOL "Set to ON to build with Qmoorie" FORCE)

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")