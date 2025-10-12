#include "../include/calculator.h"
#include <iostream>
#include <ostream>

int main(const int argc, char* argv[])
{
    if (argc != 4)
    {
        // I use 'x' for multiplication because otherwise calling it from the terminal performs a bash substitution
        std::cerr << "Usage: <x1> <x2> <op [+|-|x|/]>" << std::endl;
        return 1;
    }

    const double x1{std::strtod(argv[1], nullptr)};
    const double x2{std::strtod(argv[2], nullptr)};
    const std::string op{argv[3]};

    std::cout << "Result: " << calculate(x1, x2, op) << std::endl;

    return 0;
}
