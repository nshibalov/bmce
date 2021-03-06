cmake_minimum_required (VERSION 2.8)

project(bmce.core)

set(DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/bmce")

set(SOURCES
  ${SOURCE_DIR}/fileimport.cpp
  ${SOURCE_DIR}/mathlib.cpp
  ${SOURCE_DIR}/mesh.cpp
  ${SOURCE_DIR}/utils.cpp
  ${SOURCE_DIR}/texture.cpp
  ${SOURCE_DIR}/gl/glmesh.cpp
  ${SOURCE_DIR}/gl/glshader.cpp
  ${SOURCE_DIR}/gl/gltexture.cpp
  ${SOURCE_DIR}/log/loggable.cpp)

set(HEADERS
  ${HEADER_DIR}/core/fileimport.h
  ${HEADER_DIR}/core/constants.h
  ${HEADER_DIR}/core/camera.h
  ${HEADER_DIR}/core/event.h
  ${HEADER_DIR}/core/mathlib.h
  ${HEADER_DIR}/core/mesh.h
  ${HEADER_DIR}/core/utils.h
  ${HEADER_DIR}/core/types.h
  ${HEADER_DIR}/core/texture.h
  ${HEADER_DIR}/core/colortypes.h
  ${HEADER_DIR}/core/rect.h
  ${HEADER_DIR}/core/gl/gl.h
  ${HEADER_DIR}/core/gl/glmesh.h
  ${HEADER_DIR}/core/gl/glshader.h
  ${HEADER_DIR}/core/gl/gltexture.h
  ${HEADER_DIR}/core/log/loggable.h
  ${HEADER_DIR}/core/log/logger.h
  ${HEADER_DIR}/core/log/consolelogger.h)

include_directories(${HEADER_DIR})

set(LIBRARIES)

# OPENGL
message(STATUS "Checking OpenGL...")
find_package(OpenGL REQUIRED)
list(APPEND LIBRARIES ${OPENGL_LIBRARIES})

# GLEW
message(STATUS "Checking GLEW...")
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
list(APPEND LIBRARIES ${GLEW_LIBRARIES})

# assimp
message(STATUS "Checking Assimp...")
find_package(assimp REQUIRED)
include_directories(${assimp_INCLUDE_DIRS})
list(APPEND LIBRARIES ${assimp_LIBRARIES})

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

set(CORE_LIBRARIES ${PROJECT_NAME})
set(CORE_INCLUDE_DIRS ${HEADER_DIR} ${GLEW_INCLUDE_DIRS})

# Tests
add_subdirectory(tests)

set(CORE_DATA_DIRS ${DATA_DIR} PARENT_SCOPE)
set(CORE_LIBRARIES ${CORE_LIBRARIES} PARENT_SCOPE)
set(CORE_INCLUDE_DIRS ${CORE_INCLUDE_DIRS} PARENT_SCOPE)
