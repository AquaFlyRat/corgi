cmake_minimum_required (VERSION 3.0)
project (corgi)

set (CMAKE_CXX_STANDARD 17)
add_subdirectory (third_party)

include_directories (third_party/fmt-5.3.0/include)
include_directories (third_party/SDL2-2.0.8/include)

set (source
  src/corgi.cpp
)

add_executable (${PROJECT_NAME} ${source})

if (WIN32)
target_link_libraries(${PROJECT_NAME} mingw32)
endif()

target_link_libraries (${PROJECT_NAME} SDL2main SDL2 fmt)
