cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(normalsHoughProject)

SET(CMAKE_BUILD_TYPE Release)


set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib )

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/usr/lib/x86_64-linux-gnu/")

############################
## OPENMP
############################
if(UNIX)
	#use openMP
	find_package( OpenMP REQUIRED)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif(UNIX)

include_directories(${CMAKE_SOURCE_DIR}/include)


###########################
## Executable
add_executable(Hough_Exec src/main.cpp)
target_link_libraries(Hough_Exec ${EXTRA_LIBS} ${Boost_LIBRARIES} ${PCL_LIBRARIES} ${PROJECT_LINK_LIB} )

##########################
## Python wrapper
set(GENERATE_PYTHON_MODULE "ON" CACHE BOOL "build the python module")
if(GENERATE_PYTHON_MODULE)

	# Make the scripts available in the 'cmake' directory available for the
	# 'include()' command, 'find_package()' command.
	set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake )

	# Include the CMake script UseCython.cmake.  This defines add_cython_module().
	# Instruction for use can be found at the top of cmake/UseCython.cmake.
	include( UseCython )

	include_directories("python")

	### build the libraies in the package directory
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/python")

	add_subdirectory(python)


endif()
