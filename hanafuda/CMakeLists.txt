add_library(hanafuda)
target_sources(hanafuda PRIVATE
  include/hana/card.hpp
  src/card.cpp
  src/compress.cpp
)
target_include_directories(hanafuda PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(hanafuda PUBLIC cxx_std_11)
set_target_properties(hanafuda PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/hana/card.hpp
)
#target_link_libraries(hanafuda PUBLIC ...)
add_library(hanafuda::hanafuda ALIAS hanafuda)

#add_subdirectory(tests)

# Install
install(TARGETS hanafuda
  EXPORT hanafudaTargets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/hana
)
