#include <complex>
#include <cstddef>
#include <iostream>
#include <ostream>

class DataProcessor
{
public:
    DataProcessor(const double v[], const std::size_t& v_size) : data_size(v_size)
    {
        data = new double[data_size];
        for (int i = 0; i < v_size; i++)
        {
            data[i] = v[i];
        }
    }

    ~DataProcessor()
    {
        delete[] data;
    }

    DataProcessor(const DataProcessor& other) : data_size(other.data_size)
    {
        data = new double[data_size];
        for (int i = 0; i < other.data_size; i++)
        {
            data[i] = other.data[i];
        }
    }

    DataProcessor& operator=(const DataProcessor& other)
    {
        if (this != &other)
        {
            data = new double[data_size];
            for (int i = 0; i < other.data_size; i++)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    std::size_t n_elements()
    {
        return data_size;
    }

    double max()
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

    double min()
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

    double mean()
    {
        return sum() / data_size;
    }

    double stddev()
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

    double sum()
    {
        double sum = data[0];
        for (int i = 1; i < data_size; i++)
        {
            sum += data[i];
        }
        return sum;
    }

private:
    double *data;
    const std::size_t data_size;
};

bool testMax()
{
    double data[]{2, 1, 3, 5, 4};
    DataProcessor d{data, 5};
    return d.max() == 5;
}
bool testMin()
{
    double data[]{2, 1, 3, 5, 4};
    DataProcessor d{data, 5};
    return d.min() == 1;
}
bool testMean()
{
    double data[]{2, 1, 3, 5, 4};
    DataProcessor d{data, 5};
    return d.mean() == 3;
}
bool testStddev()
{
    double data[]{2, 1, 3, 5, 4};
    DataProcessor d{data, 5};
    return d.stddev() == 1.414213562;
}

int main()
{
    bool r = testMax();
    r = testMin();
    r = testMean();
    r = testStddev();

}

