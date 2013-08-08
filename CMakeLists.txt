project(LibFi)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

set(Boost_ADDITIONAL_VERSIONS "1.47" "1.47.0")
set(REQ_BOOST_LIBS)
set(REQ_BOOST_LIBS ${REQ_BOOST_LIBS} unit_test_framework)
find_package(Boost 1.39.0 REQUIRED ${REQ_BOOST_LIBS})

link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include/)

set(CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra")

add_subdirectory (tests) 
add_subdirectory (samples) 
