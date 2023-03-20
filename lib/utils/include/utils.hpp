#ifndef UTILS_HPP
#define UTILS_HPP
#include <vector>
std::vector<std::string> splitString (std::string toSplit, char separator);
int findInVector (std::vector<std::string> input, std::string value);
struct Movie {
    std::string tconst;
    std::string originName;
};
int findInMovieVector (std::vector<Movie> input, std::string value);
#endif 
