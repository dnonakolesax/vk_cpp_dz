file (GLOB SOURCES src/*.cpp)

add_library (operations ${SOURCES})
target_include_directories (operations PUBLIC include)