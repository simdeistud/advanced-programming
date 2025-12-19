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

double StatisticsToolkit::median(const std::vector<double>& data) {
	/* Since the median can be computed on basically any type which is comparable,
	   I create a vector of references and order it based on their dereferenced value.
	   In this way, I can ensure const correctness without sacrificing performance copying
	   an entire vector of arbitrarily big data.
	*/
	std::vector<std::reference_wrapper<const double>> refs{data.begin(), data.end()};
    std::sort(refs.begin(),
              refs.end(),
			  [](const std::reference_wrapper<const double> a, const std::reference_wrapper<const double> b) { return a.get() < b.get(); }
			  );
	if (data.size() % 2 != 0) {
		return refs.at(data.size()/2).get();
	}
	return std::midpoint(refs.at((data.size() - 1)/2).get(), refs.at(data.size()/2).get());
}

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
 * - The median should return a reference to the original object instead of creating a copy
 */