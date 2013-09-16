include_directories(
	${PROJECT_SOURCE_DIR}/include
)

add_executable(fixed ${PROJECT_SOURCE_DIR}/tools/fixed.cpp)
target_link_libraries(fixed ${Boost_LIBRARIES})
