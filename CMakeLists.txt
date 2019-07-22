cmake_minimum_required (VERSION 3.0)
project (corgi)

set (CMAKE_CXX_STANDARD 17)
add_subdirectory (third_party)

include_directories (third_party/fmt-5.3.0/include)
include_directories (third_party/glm-0.9.9.5/include)
include_directories (third_party/SDL2-2.0.8/include)

set (source
  src/corgi.cpp
  src/window.cpp
)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable (${PROJECT_NAME} ${source})

if(MINGW)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

if (WIN32)
target_link_libraries(${PROJECT_NAME} mingw32)
endif()

target_link_libraries (${PROJECT_NAME} SDL2main SDL2 fmt)
