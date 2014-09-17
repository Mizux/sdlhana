cmake_minimum_required(VERSION 2.8)
project(hanafuda)

include_directories("include")
set(${PROJECT_NAME}_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
 CACHE PATH "${PROJECT_NAME} include path")

file(GLOB_RECURSE _HDRS include/*.hpp)
file(GLOB_RECURSE _SRCS src/*.cpp src/*.hpp)

add_library(${PROJECT_NAME} ${_HDRS} ${_SRCS})
target_link_libraries(${PROJECT_NAME}
)
