#include "eqparser.hpp"

#include <stack>
#include <queue>
#include <iostream>
#include <sstream>
#include <regex>
#include <vector>

std::vector<std::string> splitString(std::string toSplit, char separator) {
    std::stringstream ss(toSplit);
    std::string temp;
    std::vector<std::string> result;
    while (std::getline(ss, temp, separator)) {
        result.push_back(temp);
    }
    return result;
}

bool isOperator(std::string input) {
    if ((input == PLUS_SIGN) || (input == MINUS_SIGN) || (input == DIVIDE_SIGN) || (input == COS_SIGN) || (input == TAN_SIGN))
        return true;
    return false;    
}

bool isDigit(std::string input) {
    std::regex doubleRegex ("[+-]?([0-9]*[.])?[0-9]+");
    if (std::regex_search(input, doubleRegex))
        return true;
    return false; 
}

std::vector<std::string> infixToPostfix(std::string eq) {
    std::vector<std::string> postfix;
    std::stack <std::string> postfixStack;
    auto infix = splitString(eq, ' ');
    for (size_t i=0; i<infix.size(); i++) {
        if (isDigit(infix[i])) 
            postfix.push_back(infix[i]);
        if (isOperator(infix[i]))
            if (postfixStack.empty() || postfixStack.top() == LBRACKET_SIGN)
                postfixStack.push(infix[i]);
            else
            if (operationPriorities[infix[i]] > operationPriorities[postfixStack.top()])
                postfixStack.push(infix[i]);
            else {
                while ( ((!postfixStack.empty()) && (operationPriorities[postfixStack.top()] >= operationPriorities[infix[i]]) && (postfixStack.top()!=LBRACKET_SIGN))) {
                    postfix.push_back(postfixStack.top());
                    postfixStack.pop();
                }
                postfixStack.push(infix[i]);
            }       
        if (infix[i] == LBRACKET_SIGN)
            postfixStack.push(infix[i]);
        if (infix[i] == RBRACKET_SIGN) {
            while (postfixStack.top()!=LBRACKET_SIGN) {
                postfix.push_back(postfixStack.top());
                postfixStack.pop();
            }
            postfixStack.pop();    
        }
    }
    while (!postfixStack.empty()) {
        postfix.push_back(postfixStack.top());
        postfixStack.pop();
    }
    return postfix;
}

ICalculatable* buildEqTree (std::string equation) {
    std::stack<ICalculatable*> s;
    auto postfix = infixToPostfix(equation);
    for (size_t i = 0; i<postfix.size(); i++) {
        if (isDigit(postfix[i]))
            s.push(new Number(stod(postfix[i])));
        if (isOperator(postfix[i])) {
            if (operationTypes[postfix[i]]==BINARY_OPERATION) {
                ICalculatable* left = s.top();
                s.pop();
                ICalculatable* right = s.top();
                s.pop();
                if (postfix[i] == PLUS_SIGN)
                    s.push(new Plus(left, right));
                if (postfix[i] == MINUS_SIGN)
                    s.push(new Minus(left, right));
                if (postfix[i] == DIVIDE_SIGN)
                    s.push(new Divide(right, left)); 
            } else {
                ICalculatable* val = s.top();
                s.pop();
                if (postfix[i] == TAN_SIGN)
                    s.push(new Tan(val));
                if (postfix[i] == COS_SIGN)
                    s.push(new Cos(val));
            }               
        }
    }
    return s.top();
}