#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include "StatisticsToolkit.hpp"

int main() {
    // Test mean function
    const std::vector<double> v = std::vector{1.0, 2.0, 3.0};
    assert(StatisticsToolkit::mean(v) == 2.0);

    // Test variance function
    assert(StatisticsToolkit::variance(v) == 2.0 / 3.0);
    // Test stddev function
    assert(StatisticsToolkit::std_dev(v) == std::sqrt(2.0 / 3.0));

    // Test count function
    assert(StatisticsToolkit::count(v, 3.0) == 1);
    // Test frequency table function
    std::cout << StatisticsToolkit::frequency_map(v)[3.0] << std::endl;
    assert(StatisticsToolkit::frequency_map(v)[3.0] == 1);

    return 0;
}