cmake_minimum_required (VERSION 3.0)
project (corgi)

include (${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup ()

set (source
  src/corgi.cpp
)

add_executable (${PROJECT_NAME} ${source})
target_link_libraries (${PROJECT_NAME} ${CONAN_LIBS})
