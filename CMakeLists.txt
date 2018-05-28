cmake_minimum_required (VERSION 2.8)

project(bmce)

set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party")

set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# google test

if (MSVC)
  set(gtest_force_shared_crt ON CACHE BOOL "")
endif()
add_subdirectory(${THIRD_PARTY_DIR}/googletest)

enable_testing()

# project

if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    add_compile_options(
      -std=c++14
      -Wpedantic
      -Wall
      -Wextra
      -O3
      -g
      -pipe)
endif(CMAKE_COMPILER_IS_GNUCXX)

add_subdirectory(core)
add_subdirectory(gui)
add_subdirectory(arcade)
