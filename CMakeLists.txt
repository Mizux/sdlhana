cmake_minimum_required(VERSION 2.8)
project(sdlhana)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(tools)
add_subdirectory(hanafuda)
add_subdirectory(hanafuda_app)
