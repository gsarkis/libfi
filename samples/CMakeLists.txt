add_executable(fixed ${PROJECT_SOURCE_DIR}/samples/fixed.cpp)
target_link_libraries(fixed ${Boost_LIBRARIES})

add_executable(sample_simple ${PROJECT_SOURCE_DIR}/samples/sample_simple.cpp)
target_link_libraries(sample_simple ${Boost_LIBRARIES})
