cmake_minimum_required(VERSION 2.6)

project(iazappy)
set(iazappy_VERSION_MAJOR 0)
set(iazappy_VERSION_MINOR 3)

ADD_DEFINITIONS(-Wall -std=c++0x -ggdb -g3)


include_directories(
	./Srcs/
)

file(
	GLOB_RECURSE
	source_files
	Srcs/*
)

add_executable(
	${PROJECT_NAME}
	${source_files}
)

target_link_libraries(
    ${PROJECT_NAME}
    lua
    boost_system
    boost_regex
    boost_program_options
    pthread
    dl
)
