cmake_minimum_required(VERSION 2.6)

project(iazappy)

ADD_DEFINITIONS(-Wall -std=c++0x)


include_directories(
	./srcs/
)

file(
	GLOB_RECURSE
	source_files
	srcs/*
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
pthread
)
