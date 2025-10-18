//
// Created by simone on 18/10/25.
//
#ifndef ADVANCED_PROGRAMMING_DATAPROCESSOR_H
#define ADVANCED_PROGRAMMING_DATAPROCESSOR_H


class DataProcessor
{
public:
    DataProcessor(const double v[], const int& v_size) : data_size(v_size)
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

    int n_elements()
    {
        return data_size;
    }

    double max();
    double min();
    double mean();
    double stddev();
    double sum();

private:
    double *data;
    const int data_size;
};


#endif //ADVANCED_PROGRAMMING_DATAPROCESSOR_H