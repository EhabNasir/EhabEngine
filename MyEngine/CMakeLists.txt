cmake_minimum_required(VERSION 3.20)
project(MyEngine)

set(CMAKE_CXX_STANDARD 20)

set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(external/bgfx.cmake)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(MyEngine ${SOURCES})

target_include_directories(MyEngine
    PRIVATE
    src
    external/bgfx/include
    external/bx/include
    external/bimg/include
)

target_link_libraries(MyEngine
    PRIVATE
    bgfx
    bx
    bimg
)
