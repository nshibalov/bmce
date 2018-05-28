cmake_minimum_required (VERSION 2.8)

project(test_quaternion)

set(SOURCES
  test_quaternion.cpp)

set(LIBRARIES
  gtest_main
  ${CORE_LIBRARIES})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

add_test(
  NAME ${PROJECT_NAME}
  COMMAND ${OUTPUT_DIRECTORY}/${PROJECT_NAME}
  WORKING_DIRECTORY ${OUTPUT_DIRECTORY})
