file (GLOB SOURCES src/*.cpp)

add_library (eqparser ${SOURCES})
target_include_directories (eqparser PUBLIC include)

target_link_libraries (eqparser operations)