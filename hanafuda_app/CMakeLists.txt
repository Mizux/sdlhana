project(sdlhanafuda VERSION 0.1)

# SDL
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
#find_package(SDL3_ttf REQUIRED)
#find_package(SDL3_mixer REQUIRED)

file(GLOB_RECURSE _SRCS src/*.cpp src/*.hpp)
add_executable(${PROJECT_NAME} ${_SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE src)
# note: macOS is APPLE and also UNIX !
if(APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    INSTALL_RPATH "@loader_path/../${CMAKE_INSTALL_LIBDIR}")
elseif(UNIX AND NOT APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
endif()
add_executable(${PROJECT_NAMESPACE}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE
  SDL3::SDL3
  SDL3_image::SDL3_image
  hanafuda::hanafuda
)
