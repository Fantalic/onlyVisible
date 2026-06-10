cmake_minimum_required(VERSION 3.20)
project(onlyVisible LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES src/*.cpp)

include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build raylib as a static library")
set(BUILD_EXAMPLES OFF CACHE BOOL "Build raylib examples")
FetchContent_MakeAvailable(raylib)

add_executable(Game ${SOURCES})
target_include_directories(Game PRIVATE include)
target_link_libraries(Game PRIVATE raylib)
