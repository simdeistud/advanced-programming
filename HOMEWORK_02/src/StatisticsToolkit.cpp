#include <vector>
#include <unordered_map>
#include <cmath>
#include <numeric>
#include <functional>
#include <algorithm>
#include "StatisticsToolkit.hpp"

double StatisticsToolkit::mean(const std::vector<double>& data) {
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

/*double StatisticsToolkit::median(const std::vector<double>& data) {

}*/

double StatisticsToolkit::variance(const std::vector<double>& data) {
    auto m = StatisticsToolkit::mean(data);
    return std::transform_reduce(data.begin(), data.end(), 0.0, std::plus<double>{}, [&m](double x) {return std::pow(x - m, 2);}) / data.size();
}

double StatisticsToolkit::std_dev(const std::vector<double>& data) {
    return std::sqrt(StatisticsToolkit::variance(data));
}

std::size_t StatisticsToolkit::count(const std::vector<double>& data, const double& element) {
    return std::count(data.begin(), data.end(), element);
}

std::unordered_map<double, std::size_t> StatisticsToolkit::frequency_map(const std::vector<double>& data) {
    std::unordered_map<double, std::size_t> freq_map = std::unordered_map<double, std::size_t>();
    for (auto e : data) {
        if (freq_map.contains(e)) {
            ++freq_map.at(e);
        } else {
            freq_map.emplace(e, 1);
        }
    }
    return freq_map;
}

/* TODO
 * - When templatizing the library, use the equality_comparable concept for the count and frequency map, and the totally_ordered concept for the median
 * - The median should order pointers to the elements based on their value, as to maintain const correctness and proper performance
 */