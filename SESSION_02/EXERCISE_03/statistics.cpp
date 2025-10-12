#include "statistics.hpp"
#include <algorithm>
#include <cmath>

namespace stat
{
    // Function to calculate the mean of a set of numbers.
    double calculate_mean(const std::vector<double>& numbers)
    {
        double sum{0};
        for (const double& n : numbers)
        {
            sum += n;
        }
        return sum / numbers.size();
    }

    double calculate_squared_mean(const std::vector<double>& numbers)
    {
        double sum{0};
        for (const double& n : numbers)
        {
            sum += pow(n, 2);
        }
        return sum / numbers.size();
    }

    // Function to calculate the median of a set of numbers.
    double calculate_median(const std::vector<double>& numbers)
    {
        std::vector<double> ordered{numbers.begin(), numbers.end()};
        std::sort(ordered.begin(), ordered.end());
        return ordered.at(ordered.size() / 2);
    }

    // Function to calculate the standard deviation of a set of numbers.
    double calculate_standard_deviation(const std::vector<double>& numbers)
    {
        const double eX2{calculate_squared_mean(numbers)};
        const double e2X{std::pow(calculate_mean(numbers), 2)};
        return std::sqrt(eX2 - e2X);
    }
} // namespace stat
