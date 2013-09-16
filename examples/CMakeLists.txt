include_directories(
	${PROJECT_SOURCE_DIR}/include
)

add_executable(example_simple ${PROJECT_SOURCE_DIR}/examples/example_simple.cpp)
target_link_libraries(example_simple ${Boost_LIBRARIES})
