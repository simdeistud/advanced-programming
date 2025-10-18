#include <iostream>
#include "DataProcessor.h"

int main()
{
    double data[]{2, 1, 3, 5, 4};
    DataProcessor d{data, 5};
    std::cout << "Data = [";
    for (double i : data)
    {
        std::cout << i << ",";
    }
    std::cout << "]" << std::endl;

    std::cout << "Max: " << d.max() << std::endl;
    std::cout << "Min: " << d.min() << std::endl;
    std::cout << "Mean: " << d.mean() << std::endl;
    std::cout << "Standard dev: " << d.stddev() << std::endl;

}

