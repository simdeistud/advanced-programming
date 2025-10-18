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

private:
    double *data;
    const std::size_t data_size;
};

int main()
{
    double data[]{2.0, 3.5, 0.93, 52322};
    DataProcessor dataProcessor(data, 4);
    DataProcessor dataProcessorCopyConst(dataProcessor);
    DataProcessor dataProcessorCopyOp = dataProcessor;
    std::cout << "Original data:" << std::endl;
    for (double i : data)
    {
        std::cout << i << std::endl;
    }
}