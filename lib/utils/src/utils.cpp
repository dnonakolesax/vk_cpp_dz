#include <string>
#include <vector>
#include <sstream>
#include "utils.hpp"


std::vector<std::string> splitString (std::string toSplit, char separator) {
    std::stringstream ss(toSplit);
    std::string temp;
    std::vector<std::string> result;
    while (std::getline(ss, temp, separator)) {
        result.push_back(temp);
    }
    return result;
}