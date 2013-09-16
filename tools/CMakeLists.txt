#boost pre-processor
set(REQ_BOOST_LIBS ${REQ_BOOST_LIBS})

include_directories(
	${PROJECT_SOURCE_DIR}/include
)

add_executable(fixed ${PROJECT_SOURCE_DIR}/tools/fixed.cpp)
