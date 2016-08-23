cmake_minimum_required(VERSION 2.8)

project(mu-refreshy)

# Options

option(BUILD_TESTS "Build tests" OFF)
message(STATUS "BUILD_TESTS: ${BUILD_TESTS}")

# Project version

set(mu-refreshy_VERSION_MAJOR 0)
set(mu-refreshy_VERSION_MINOR 1)
set(mu-refreshy_VERSION_PATCH 2)
set(mu-refreshy_VERSION ${mu-refreshy_VERSION_MAJOR}.${mu-refreshy_VERSION_MINOR}.${mu-refreshy_VERSION_PATCH})

# CMake flags

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(CMAKE_CXX_FLAGS "-std=c++11 -pthread -W -Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

# Build type

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
	set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Find packages

set(BOOST_REQUIRED_LIBS system filesystem program_options)
if(BUILD_TESTS)
	set(BOOST_REQUIRED_LIBS ${BOOST_REQUIRED_LIBS} unit_test_framework)
	find_package(FakeIt REQUIRED)
endif()

find_package(Boost REQUIRED COMPONENTS ${BOOST_REQUIRED_LIBS})
find_package(MusicBrainz5 REQUIRED)
find_package(TagLib REQUIRED)

set(PROJECT_BUILD_LIBRARY murefreshy)
set(BUILD_LIBRARIES
	boost_system
	boost_filesystem
	boost_program_options
	tag
	musicbrainz5
	${PROJECT_BUILD_LIBRARY}
)

# Build

file(GLOB_RECURSE sources "src/*/*.cpp")

include_directories(
	${CMAKE_SOURCE_DIR}/include
)

add_library(${PROJECT_BUILD_LIBRARY} STATIC ${sources})
add_executable(${PROJECT_NAME} "src/murefreshy.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED ON
)
target_link_libraries(${PROJECT_NAME} ${BUILD_LIBRARIES})

# Tests

if(BUILD_TESTS)
	include_directories(${FAKEIT_INCLUDE_DIRS})
	enable_testing()
	file(GLOB_RECURSE tests "tests/*.cpp")
	foreach(test_file ${tests})
		get_filename_component(test_name ${test_file} NAME_WE)

		file(RELATIVE_PATH test_path ${CMAKE_SOURCE_DIR}/tests ${test_file})
		get_filename_component(test_path ${test_path} DIRECTORY)
		if(NOT "${test_path}" STREQUAL "")
			string(REPLACE "/" "_" test_path ${test_path})
			set(test_name "${test_path}_${test_name}")
		endif()

		add_executable(${test_name} ${test_file})
		target_compile_definitions(${test_name} PRIVATE "BOOST_TEST_DYN_LINK=1")
		target_link_libraries(${test_name} ${BUILD_LIBRARIES} boost_unit_test_framework)
		set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)
		add_test(NAME ${test_name} COMMAND ${test_name})
	endforeach()
endif()

# Install

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
