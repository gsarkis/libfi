project(LibFi-unit-tests CXX)

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)


set(Boost_ADDITIONAL_VERSIONS "1.47" "1.47.0")
set(REQ_BOOST_LIBS)
set(REQ_BOOST_LIBS ${REQ_BOOST_LIBS} unit_test_framework)

set(CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra")

find_package(Boost 1.39.0 REQUIRED ${REQ_BOOST_LIBS})

link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(include/)

include(CTest)
enable_testing()
set(CTEST_OUTPUT_ON_FAILURE ON)

set(BUILDNAME "${BUILDNAME}" CACHE STRING "Name of build on the dashboard")

file(GLOB tests "tests/*_test.cpp")
foreach( test_path ${tests} )
  get_filename_component(testname ${test_path} NAME_WE)
  string(REGEX REPLACE "_test" "" test "${testname}")
  message(STATUS "Adding test ${test}")
  add_executable(${test} ${PROJECT_SOURCE_DIR}/tests/${testname}.cpp)
  target_link_libraries(${test} ${Boost_LIBRARIES})
  add_test(${test} ${CMAKE_CURRENT_BINARY_DIR}/${test})
endforeach()
