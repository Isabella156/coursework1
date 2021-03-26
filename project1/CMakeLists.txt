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

#4.source directory，源文件目录
AUX_SOURCE_DIRECTORY(src DIR_SRCS)

#5.set environment variable，设置环境变量，编译用到的源文件全部都要放到这里，否则编译能够通过，但是执行的时候会出现各种问题，比如"symbol lookup error xxxxx , undefined symbol"
SET(TEST_MATH
${DIR_SRCS}
)

add_executable(project1 ${SOURCES})
