file (GLOB SOURCES src/*.cpp)

add_library (IMDbParser ${SOURCES})
target_include_directories (IMDbParser PUBLIC include)
target_link_libraries (IMDbParser utils)