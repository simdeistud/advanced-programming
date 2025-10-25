#include <iostream>
#include "DataProcessor.h"

double compute_correlation(const DataProcessor &dp1, const DataProcessor &dp2)
{

    auto* cov = &((dp1 - dp1.mean())*(dp2 - dp2.mean()));
    return cov->mean() / (dp1.stddev() * dp2.stddev());
}

int main()
{
    const DataProcessor d1{new double[]{2, 1, 3, 5, 4}, 5};
    const DataProcessor d2{new double[]{20, 11, 3.23, 742, 0}, 5};
    const DataProcessor d3{new double[]{2, 1, 3, 5}, 4};
    const DataProcessor d4 = d2;
    const DataProcessor d5 = DataProcessor(d2);

    std::cout << "d1 = " << d1 << std::endl;
    std::cout << "Max: " << d1.max() << std::endl;
    std::cout << "Min: " << d1.min() << std::endl;
    std::cout << "Mean: " << d1.mean() << std::endl;
    std::cout << "Standard dev: " << d1.stddev() << std::endl;
    std::cout << "d2 = " << d2 << std::endl;
    d2[1] = 777;
    std::cout << "d4 (= override) = " << d4 << std::endl;
    std::cout << "d5 (copy constructor) = " <<  d5<< std::endl;
    std::cout << "d1 + d2 = " << d1 + d2 << std::endl;
    std::cout << "d2 - 1000 = " << d2 - 1000 << std::endl;
    std::cout << "d2 + d3 = " << d2 + d3 << std::endl;
    std::cout << "corr(d1, d2) = " << compute_correlation(d1, d2) << std::endl;
}
