#include <string>
#include <vector>
#include <sstream>
#include "utils.hpp"

std::vector<std::string> splitString (std::string toSplit, char separator) {
    std::stringstream ss(toSplit);
    std::string temp;
    std::vector<std::string> result;
    while (std::getline(ss, temp, separator)) {
        result.push_back (temp);
    }
    return result;
}

int findInVector (std::vector<std::string> input, std::string value) {
    for (size_t i=0; i<input.size(); i++) {
        if (input[i]==value) return i;
    }
    return -1;
}

int findInMovieVector (std::vector<Movie> input, std::string value) {
    for (size_t i=0; i<input.size(); i++) {
        if (input[i].tconst==value) return i;
    }
    return -1;
}