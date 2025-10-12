#include "../include/calculator.h"
#include <functional>

double calculate(const double& x1, const double& x2, const std::string& op)
{
    if (op == "+")
    {
        return add(x1, x2);
    }
    if (op == "-")
    {
        return sub(x1, x2);
    }
    if (op == "x")
    {
        return mul(x1, x2);
    }
    if (op == "/")
    {
        return div(x1, x2);
    }

    return 0.0;
}

double add(const double& x1, const double& x2)
{
    return x1 + x2;
}
double sub(const double& x1, const double& x2)
{
    return x1 - x2;
}
double mul(const double& x1, const double& x2)
{
    return x1 * x2;
}
double div(const double& x1, const double& x2)
{
    return x1 / x2;
}