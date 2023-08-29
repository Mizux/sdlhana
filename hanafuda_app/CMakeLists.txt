project(sdlhanafuda VERSION 0.1)

# SDL
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
#find_package(SDL_ttf REQUIRED)
#find_package(SDL_mixer REQUIRED)

include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDLIMAGE_INCLUDE_DIR})
#include_directories(${SDLTTF_INCLUDE_DIR})
#include_directories(${SDLMIXER_INCLUDE_DIR})

file(GLOB_RECURSE _SRCS src/*.cpp src/*.hpp)
add_executable(${PROJECT_NAME} ${_SRCS})
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
  ${SDL_LIBRARY} ${SDLMAIN_LIBRARY}
  ${SDLIMAGE_LIBRARY}
  #${SDLTTF_LIBRARY}
  #${SDLMIXER_LIBRARY}
  hanafuda::hanafuda
)
