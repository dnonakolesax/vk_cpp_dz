#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> splitString (std::string toSplit, char separator) {
    std::stringstream ss(toSplit);
    std::string temp;
    std::vector<std::string> result;
    while (std::getline(ss, temp, separator)) {
        result.push_back (temp);
    }
    return result;
}

bool findInVector (std::vector<std::string> input, std::string value) {
    for (size_t i=0; i<input.size(); i++) {
        if (input[i]==value) return true;
    }
    return false;
}