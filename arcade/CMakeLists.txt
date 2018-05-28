cmake_minimum_required (VERSION 2.8)

project(bmce.arcade)


set(DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(SOURCES
  ${SOURCE_DIR}/main.cpp)

set(LIBRARIES)

# GLFW3
message(STATUS "Checking GLFW3...")
find_package(glfw3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIR})
list(APPEND LIBRARIES ${GLFW3_LIBRARY})

# core
include_directories(${CORE_INCLUDE_DIRS})
list(APPEND LIBRARIES ${CORE_LIBRARIES})

# gui
include_directories(${GUI_INCLUDE_DIRS})
list(APPEND LIBRARIES ${GUI_LIBRARIES})

# make exe
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

# copy data
file(COPY ${CORE_DATA_DIRS} DESTINATION ${OUTPUT_DIRECTORY})
file(COPY ${DATA_DIR} DESTINATION ${OUTPUT_DIRECTORY})
