//
// Created by simone on 16/11/25.
//
#include <iostream>
#include <ostream>

#include "ADExpression.h"

int main()
{
    const ADExpression* f = new Difference(new Sum(new Difference(new Product(new Scalar(2), new Power(new Variable(), new Scalar(3))), new Product(new Scalar(3), new Power(new Variable(), new Scalar(2)))), new Product(new Scalar(4), new Variable())), new Scalar(5));
    std::cout << "f(x) = 2*x^3 - 3*x^2 + 4*x - 5" << std::endl;
    std::cout << "f(2) = " << f->evaluate(2) << std::endl;
    std::cout << "f'(2) = " << f->derivative(2) << std::endl;
    std::cout << std::endl;

    const ADExpression* g = new Division(new Scalar(1), new Variable());
    std::cout << "g(x) = 1/x " << std::endl;
    std::cout << "g(2) = " << g->evaluate(2) << std::endl;
    std::cout << "g'(2) = " << g->derivative(2) << std::endl;
    std::cout << std::endl;

    return 0;
}