//
// Created by simone on 16/11/25.
//

#ifndef ADVANCED_PROGRAMMING_ADEXPRESSION_H
#define ADVANCED_PROGRAMMING_ADEXPRESSION_H
#include <cmath>

class ADExpression
{
public:
    virtual ~ADExpression() = default;
    virtual double evaluate(double x) const = 0;
    virtual double derivative(double x) const = 0;

};

class Scalar final : public ADExpression
{
public:
    explicit Scalar(const double value) : value{value} {}
    double evaluate(const double x) const override { return value; }
    double derivative(const double x) const override { return 0; }

private:
    const double value;
};

class Variable final : public ADExpression
{
public:
    double evaluate(const double x) const override { return x; }
    double derivative(const double x) const override { return 1; }
};

class Sum final : public ADExpression
{
public:
    Sum(const ADExpression* left, const ADExpression* right) : left{left}, right{right} {};
    double evaluate(const double x) const override { return left->evaluate(x) + right->evaluate(x); }
    double derivative(const double x) const override { return left->derivative(x) + right->derivative(x); }

private:
    const ADExpression* left;
    const ADExpression* right;
};

class Difference final : public ADExpression
{
public:
    Difference(const ADExpression* left, const ADExpression* right) : left{left}, right{right} {};
    double evaluate(const double x) const override { return left->evaluate(x) - right->evaluate(x); }
    double derivative(const double x) const override { return left->derivative(x) - right->derivative(x); }

private:
    const ADExpression* left;
    const ADExpression* right;
};

class Product final : public ADExpression
{
public:
    Product(const ADExpression* left, const ADExpression* right) : left{left}, right{right} {};
    double evaluate(const double x) const override { return left->evaluate(x) * right->evaluate(x); }
    double derivative(const double x) const override { return left->derivative(x)*right->evaluate(x) + right->derivative(x)*left->evaluate(x); }

private:
    const ADExpression* left;
    const ADExpression* right;
};

class Division final : public ADExpression
{
public:
    Division(const ADExpression* num, const ADExpression* den) : num{num}, den{den} {};
    double evaluate(const double x) const override { return num->evaluate(x) / den->evaluate(x); }
    double derivative(const double x) const override { return (num->derivative(x)*den->evaluate(x) - den->derivative(x)*num->evaluate(x))/(den->evaluate(x)*den->evaluate(x)); }

private:
    const ADExpression* num;
    const ADExpression* den;
};

class Power final : public ADExpression
{
public:
    Power(const ADExpression* base, const Scalar* exp) : base{base}, exp{exp} {};
    double evaluate(const double x) const override { return std::pow(base->evaluate(x), exp->evaluate(x)); }
    double derivative(const double x) const override { return exp->evaluate(x) * std::pow(base->evaluate(x), exp->evaluate(x) - 1); }

private:
    const ADExpression* base;
    const Scalar* exp;
};


#endif //ADVANCED_PROGRAMMING_ADEXPRESSION_H