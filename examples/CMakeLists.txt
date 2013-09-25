include_directories(
	${PROJECT_SOURCE_DIR}/include
)

add_executable(simple ${PROJECT_SOURCE_DIR}/examples/simple.cpp)
target_link_libraries(simple ${Boost_LIBRARIES})
