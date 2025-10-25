#include <iostream>
#include "DataProcessor.h"

int main()
{
    const DataProcessor d{new double[]{2, 1, 3, 5, 4}, 5};
    std::cout << d << std::endl;

    std::cout << "Max: " << d.max() << std::endl;
    std::cout << "Min: " << d.min() << std::endl;
    std::cout << "Mean: " << d.mean() << std::endl;
    std::cout << "Standard dev: " << d.stddev() << std::endl;

    d[2] = 77;
    std::cout << d << std::endl;
}
