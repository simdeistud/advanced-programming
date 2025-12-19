#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include "StatisticsToolkit.hpp"

int main() {
    const std::vector<double> v1 = std::vector{1.0, 3.0, 2.0};

    // Test mean function
    assert(StatisticsToolkit::mean(v1) == 2.0);
    // Test median function
    assert(StatisticsToolkit::median(v1) == 2.0);
    // Test variance function
    assert(StatisticsToolkit::variance(v1) == 2.0 / 3.0);
    // Test stddev function
    assert(StatisticsToolkit::std_dev(v1) == std::sqrt(2.0 / 3.0));

    const std::vector<double> v2 = std::vector{1.0, 2.0, 3.0, 1.0};
    // Test count function
    assert(StatisticsToolkit::count(v2, 1.0) == 2);
    // Test frequency table function
    assert(StatisticsToolkit::frequency_map(v2)[1.0] == 2);

    return 0;
}