cmake_minimum_required (VERSION 2.8)

project(nwgui)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/bmce")

set(SOURCES
  ${SOURCE_DIR}/faceid.cpp
  ${SOURCE_DIR}/textrender.cpp
  ${SOURCE_DIR}/textconstraints.cpp
  )

set(HEADERS
  ${HEADER_DIR}/gui/gui.h
  ${HEADER_DIR}/gui/font.h
  ${HEADER_DIR}/gui/faceid.h
  ${HEADER_DIR}/gui/textrender.h
  ${HEADER_DIR}/gui/textconstraints.h
  )

include_directories(${HEADER_DIR})
set_source_files_properties(
  ${HEADER_DIR}/utf8/checked.h
  PROPERTIES
  COMPILE_FLAGS
  -Wno-shadow
  )

set(LIBRARIES)

# FreeType
message(STATUS "Checking FreeType...")
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
list(APPEND LIBRARIES ${FREETYPE_LIBRARIES})

# core
include_directories(${CORE_INCLUDE_DIRS})
list(APPEND LIBRARIES ${CORE_LIBRARIES})

# make gui lib
add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

set(GUI_LIBRARIES ${PROJECT_NAME})
set(GUI_INCLUDE_DIRS
  ${HEADER_DIR}
  ${FREETYPE_INCLUDE_DIRS})

# tests
add_subdirectory(tests)

set(GUI_LIBRARIES ${GUI_LIBRARIES} PARENT_SCOPE)
set(GUI_INCLUDE_DIRS ${GUI_INCLUDE_DIRS} PARENT_SCOPE)
