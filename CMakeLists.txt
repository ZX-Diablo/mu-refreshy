cmake_minimum_required(VERSION 2.8)

project(mu-refreshy)

set(mu-refreshy_VERSION_MAJOR 0)
set(mu-refreshy_VERSION_MINOR 1)
set(mu-refreshy_VERSION_PATCH 1)
set(mu-refreshy_VERSION ${mu-refreshy_VERSION_MAJOR}.${mu-refreshy_VERSION_MINOR}.${mu-refreshy_VERSION_PATCH})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(CMAKE_CXX_FLAGS "-std=c++11 -pthread -W -Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
	set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

find_package(Boost REQUIRED COMPONENTS system filesystem program_options)
find_package(MusicBrainz5 REQUIRED)
find_package(TagLib REQUIRED)

file(GLOB_RECURSE sources "src/*.cpp")

include_directories(
	${CMAKE_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME} ${sources})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME}
	boost_system
	boost_filesystem
	boost_program_options
	tag
	musicbrainz5
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
