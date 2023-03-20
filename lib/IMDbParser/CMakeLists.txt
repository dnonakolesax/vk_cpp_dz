add_library (IMDbParser src/IMDbParser.cpp)
target_include_directories (IMDbParser PUBLIC include)
target_link_libraries (IMDbParser utils)