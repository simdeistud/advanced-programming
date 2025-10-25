#include "DataProcessor.h"
#include <cmath>

double DataProcessor::max() const
{
    double max = data[0];
    for (int i = 1; i < data_size; i++)
    {
        if (max < data[i])
        {
            max = data[i];
        }
    }
    return max;
}

double DataProcessor::min() const
{
    double min = data[0];
    for (int i = 1; i < data_size; i++)
    {
        if (min > data[i])
        {
            min = data[i];
        }
    }
    return min;
}

double DataProcessor::mean() const
{
    return sum() / data_size;
}

double DataProcessor::stddev() const
{
    double stddev = 0;
    for (int i = 0; i < data_size; i++)
    {
        stddev += std::pow(data[i] - mean(), 2);
    }
    stddev /= data_size;
    stddev = sqrt(stddev);
    return stddev;
}

double DataProcessor::sum() const
{
    double sum = data[0];
    for (int i = 1; i < data_size; i++)
    {
        sum += data[i];
    }
    return sum;
}