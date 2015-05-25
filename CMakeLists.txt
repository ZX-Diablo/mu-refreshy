cmake_minimum_required(VERSION 2.8)

project(mu-refreshy)

set(mu-refreshy_VERSION_MAJOR 0)
set(mu-refreshy_VERSION_MINOR 1)
set(mu-refreshy_VERSION_PATCH 0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(MusicBrainz5 REQUIRED)
find_package(TagLib REQUIRED)

file(GLOB sources "src/*.cpp")

add_executable(${PROJECT_NAME} ${sources})
