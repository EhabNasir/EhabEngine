cmake_minimum_required(VERSION 3.20)
project(MyEngine)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(MyEngine ${SOURCES})