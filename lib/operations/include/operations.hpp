#ifndef LIB_OPERATIONS_INCLUDE_OPERATIONS_HPP_
#define LIB_OPERATIONS_INCLUDE_OPERATIONS_HPP_



#include <cmath>


class ICalculatable {
public:
  virtual double Calculate() = 0; 
};


class Number : public ICalculatable {
public:
    virtual double Calculate() override;
    explicit Number(double);
private:
    double value;
};


class Plus : public ICalculatable {
public:
    virtual double Calculate() override;
    explicit Plus(ICalculatable*, ICalculatable*);
private:
    ICalculatable* leftValue;
    ICalculatable* rightValue;   
};


class Minus : public ICalculatable {
public:
    virtual double Calculate() override;
    explicit Minus(ICalculatable*, ICalculatable*);
private:
    ICalculatable* leftValue;
    ICalculatable* rightValue;   
};


class Divide : public ICalculatable {
public:
    virtual double Calculate() override;
    explicit Divide(ICalculatable*, ICalculatable*);
private:
    ICalculatable* leftValue;
    ICalculatable* rightValue;   
};


class Cos : public ICalculatable {
public:
    virtual double Calculate() override;
    explicit Cos(ICalculatable*);
private:
    ICalculatable* value;  
};


class Tan : public ICalculatable {
public:
    virtual double Calculate() override;
    explicit Tan(ICalculatable*);
private:
    ICalculatable* value;  
};

#endif