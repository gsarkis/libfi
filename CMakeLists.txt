project(LibFi CXX)

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

OPTION (BUILD_EXAMPLES "Build example programs." FALSE)
OPTION (BUILD_TESTING "Build unit tests." TRUE)
OPTION (BUILD_TOOLS "Build tools that help in using the library." FALSE)

IF (BUILD_EXAMPLES)
	add_subdirectory(examples)
ENDIF (BUILD_EXAMPLES)

IF (BUILD_TESTING)
	include(CTest)
	enable_testing()
	add_subdirectory(tests)
ENDIF (BUILD_TESTING)

IF (BUILD_TOOLS)
	add_subdirectory(tools)
ENDIF (BUILD_TOOLS)