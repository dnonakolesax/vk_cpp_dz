file (GLOB SOURCES src/*.cpp)

add_library (utils ${SOURCES})
target_include_directories (utils PUBLIC include)