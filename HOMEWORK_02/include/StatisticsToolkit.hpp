#pragma once
#include <vector>
#include <unordered_map>

class StatisticsToolkit{
public:
    static double mean(const std::vector<double>& data);
    static double median(const std::vector<double>& data);
    static double std_dev(const std::vector<double>& data);
    static double variance(const std::vector<double>& data);
    static std::size_t count(const std::vector<double>& data, const double& element);
    static std::unordered_map<double, std::size_t> frequency_map(const std::vector<double>& data);
};