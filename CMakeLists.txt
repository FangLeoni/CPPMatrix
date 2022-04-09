cmake_minimum_required (VERSION 3.5)

project (HelloWorld)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*.cpp")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable (HelloWorld ${source_files})
target_link_libraries(HelloWorld ${CURSES_LIBRARIES})
