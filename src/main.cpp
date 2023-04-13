#include <string>
#include <iostream>

#include "eqparser.hpp"

void showUsage() {
    std::cout << "Usage: ./dz2 <equation> " << std::endl;
}


int main(int argc, char* argv[]) {
    if (argc!=2) {
        showUsage();
        return (-1);
    }
    std::string equation = argv[1];
    auto posftix = infixToPostfix(argv[1]);
    for (int i=0; i<posftix.size(); i++)
        std::cout << posftix[i] << " ";
    std::cout << std::endl;   
    auto root = buildEqTree(equation);
    std::cout << root->Calculate() << std::endl;
    return 0;
}
