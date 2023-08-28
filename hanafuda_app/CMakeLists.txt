project(sdlhanafuda)

# SDL
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
#find_package(SDL_ttf REQUIRED)
#find_package(SDL_mixer REQUIRED)
include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDLIMAGE_INCLUDE_DIR})
#include_directories(${SDLTTF_INCLUDE_DIR})
#include_directories(${SDLMIXER_INCLUDE_DIR})

include_directories(SYSTEM ${hanafuda_INCLUDE_DIRS})

file(GLOB_RECURSE _SRCS src/*.cpp src/*.hpp)

add_executable(${PROJECT_NAME} ${_SRCS})
target_link_libraries(${PROJECT_NAME}
${SDL_LIBRARY} ${SDLMAIN_LIBRARY}
${SDLIMAGE_LIBRARY}
#${SDLTTF_LIBRARY}
#${SDLMIXER_LIBRARY}
hanafuda
)
