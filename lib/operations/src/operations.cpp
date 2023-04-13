#include "operations.hpp"
#include <iostream>

Number::Number (double _value) : value(_value) {};


double Number::Calculate() {
    return value;
}


Plus::Plus (ICalculatable* _left, ICalculatable* _right) : leftValue(_left), rightValue(_right) {};


double Plus::Calculate() {
    //std::cout << "Counting " << leftValue->Calculate() << " + " << rightValue->Calculate() << std::endl;
    return leftValue->Calculate() + rightValue->Calculate();
}


Minus::Minus (ICalculatable* _left, ICalculatable* _right) : leftValue(_left), rightValue(_right) {};


double Minus::Calculate() {
    return leftValue->Calculate() - rightValue->Calculate();
}


Divide::Divide (ICalculatable* _left, ICalculatable* _right) : leftValue(_left), rightValue(_right) {};


double Divide::Calculate() {
    //std::cout << "Counting " << leftValue->Calculate() << " / " << rightValue->Calculate() << std::endl;
    return leftValue->Calculate() / rightValue->Calculate();
}


Cos::Cos (ICalculatable* _value) : value(_value) {};


double Cos::Calculate() {
    return cos(value->Calculate());
}


Tan::Tan(ICalculatable* _value) : value(_value) {};


double Tan::Calculate() {
    return tan(value->Calculate());
}