cmake_minimum_required(VERSION 2.8)

project(mu-refreshy)

set(mu-refreshy_VERSION_MAJOR 0)
set(mu-refreshy_VERSION_MINOR 1)
set(mu-refreshy_VERSION_PATCH 0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

find_package(Boost REQUIRED COMPONENTS system filesystem program_options)
find_package(MusicBrainz5 REQUIRED)
find_package(TagLib REQUIRED)

file(GLOB sources "src/*.cpp")

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
