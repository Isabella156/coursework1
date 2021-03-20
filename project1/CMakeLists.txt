cmake_minimum_required(VERSION 2.8.12)
project(project1)

# bring the headers
include_directories(include)

# change this to Release to activate optimization and compile without debug symbols
set(CMAKE_BUILD_TYPE Debug)

# adds arbitrary flags to the complier.
# this one is used to generate the files we give in input to

# can manually add the sources using the set command as follows:
# set(SOURCES src/book_management.c src/display.c src/main.c src/user.c)

# the file (GOLB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.c")

add_executable(project1 ${SOURCES})
