cmake_minimum_required (VERSION 2.8)

project(test_font)

set(SOURCES
  test_font.cpp)

set(LIBRARIES
  gtest
  gtest_main
  ${CORE_LIBRARIES}
  ${GUI_LIBRARIES})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

add_test(
  NAME ${PROJECT_NAME}
  COMMAND ${OUTPUT_DIRECTORY}/${PROJECT_NAME}
  WORKING_DIRECTORY ${OUTPUT_DIRECTORY})
