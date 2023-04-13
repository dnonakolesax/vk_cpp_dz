#ifndef LIB_EQPARSER_INCLUDE_EQPARSER_HPP_
#define LIB_EQPARSER_INCLUDE_EQPARSER_HPP_

#include <string>
#include <map>
#include <vector>

#include "operations.hpp"

#define PLUS_PRIORITY 1
#define MINUS_PRIORITY 1
#define DIVIDE_PRIORITY 2
#define TAN_PRIORITY 3
#define COS_PRIORITY 3
#define BRACKET_PRIORITY 0

#define PLUS_SIGN "+"
#define MINUS_SIGN "-"
#define DIVIDE_SIGN "/"
#define TAN_SIGN "tan"
#define COS_SIGN "cos"
#define LBRACKET_SIGN "("
#define RBRACKET_SIGN ")"

#define BINARY_OPERATION 'b'
#define UNARY_OPERATION 'u'

static std::map<std::string, int> operationPriorities = {
    {PLUS_SIGN, PLUS_PRIORITY},
    {MINUS_SIGN, MINUS_PRIORITY},
    {DIVIDE_SIGN, DIVIDE_PRIORITY},
    {LBRACKET_SIGN, BRACKET_PRIORITY},
    {RBRACKET_SIGN, BRACKET_PRIORITY},
    {TAN_SIGN, TAN_PRIORITY},
    {COS_SIGN, COS_PRIORITY}
};

static std::map<std::string, char> operationTypes = {
    {PLUS_SIGN, BINARY_OPERATION},
    {MINUS_SIGN, BINARY_OPERATION},
    {DIVIDE_SIGN, BINARY_OPERATION},
    {LBRACKET_SIGN, BINARY_OPERATION},
    {RBRACKET_SIGN, BINARY_OPERATION},
    {TAN_SIGN, UNARY_OPERATION},
    {COS_SIGN, UNARY_OPERATION}
};


std::vector<std::string> infixToPostfix(std::string infix);
ICalculatable* buildEqTree (std::string equation);

#endif