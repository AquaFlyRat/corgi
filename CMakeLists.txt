cmake_minimum_required (VERSION 3.0)
project (corgi)

add_subdirectory (third_party)

include_directories (third_party/fmt-5.3.0/include)
include_directories (third_party/SDL2-2.0.8/include)

set (source
  src/corgi.cpp
)

add_executable (${PROJECT_NAME} ${source})
target_link_libraries (${PROJECT_NAME} SDL2 SDL2main fmt)
