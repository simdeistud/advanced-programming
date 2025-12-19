class StatisticsToolkit{
public:
    static double mean(std::vector<double>& data);
    static double median(std::vector<double>& data);
    static double std_dev(std::vector<double>& data);
    static double variance(std::vector<double>& data);
    static std::size_t count(std::vector<double>& data, double& element);
    static std::unordered_map frequency_map(std::vector<double>& data);
};