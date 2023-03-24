cmake_minimum_required (VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 11)
project(dz1 VERSION 0.1.0)


add_subdirectory (lib/utils)
add_subdirectory (lib/IMDbParser)

add_executable(dz1 src/main.cpp)

target_link_libraries(dz1 IMDbParser utils)
