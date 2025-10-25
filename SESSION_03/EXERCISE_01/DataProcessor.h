//
// Created by simone on 18/10/25.
//
#ifndef ADVANCED_PROGRAMMING_DATAPROCESSOR_H
#define ADVANCED_PROGRAMMING_DATAPROCESSOR_H

#include <ostream>
#include <iostream>

class DataProcessor
{
public:
    DataProcessor(const double v[], const int v_size) : data_size(v_size)
    {
        data = new double[data_size];
        for (int i = 0; i < data_size; i++)
        {
            data[i] = v[i];
        }
        instances++;
    }

    ~DataProcessor()
    {
        delete[] data;
        instances--;
    }

    DataProcessor(const DataProcessor& other) : DataProcessor(other.data, other.data_size){}

    DataProcessor& operator=(const DataProcessor& other)
    {
        if (this != &other)
        {
            data_size = other.data_size;
            data = new double[data_size];
            for (int i = 0; i < data_size; i++)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const DataProcessor& d)
    {
        os << "[";
        for (int i = 0; i < d.data_size; i++)
        {
            os << d.data[i];
            if (i < d.data_size - 1)
            {
                os << ", ";
            }
        }
        os << "]" << std::endl;
        return os;
    }

    double& operator[](const unsigned int i) const
    {
        return data[i];
    }

    DataProcessor& operator+(const DataProcessor& d) const
    {
        if (data_size != d.data_size)
        {
            std::cerr << "Error: Cannot sum DataProcessors: Size mismatch." << std::endl;
        }
        auto* sum = new double[data_size];
        for (int i = 0; i < data_size; i++)
        {
            sum[i] = data[i] + d.data[i];
        }
        return *(new DataProcessor(sum, data_size));
    }

    DataProcessor& operator-(const DataProcessor& d) const
    {
        if (data_size != d.data_size)
        {
            std::cerr << "Error: Cannot sum DataProcessors: Size mismatch." << std::endl;
        }
        auto* sum = new double[data_size];
        for (int i = 0; i < data_size; i++)
        {
            sum[i] = data[i] - d.data[i];
        }
        return *(new DataProcessor(sum, data_size));
    }

    DataProcessor& operator-(const double d) const
    {
        auto* sum = new double[data_size];
        for (int i = 0; i < data_size; i++)
        {
            sum[i] = data[i] - d;
        }
        return *(new DataProcessor(sum, data_size));
    }

    DataProcessor& operator*(const DataProcessor& d) const
    {
        if (data_size != d.data_size)
        {
            std::cerr << "Error: Cannot sum DataProcessors: Size mismatch." << std::endl;
        }
        auto* sum = new double[data_size];
        for (int i = 0; i < data_size; i++)
        {
            sum[i] = data[i] * d.data[i];
        }
        return *(new DataProcessor(sum, data_size));
    }

    int n_elements() const
    {
        return data_size;
    }

    static int get_instances()
    {
        return instances;
    }

    double max() const;
    double min() const;
    double mean() const ;
    double stddev() const;
    double sum() const;

private:
    double* data;
    int data_size;
    inline static int instances = 0;
};


#endif //ADVANCED_PROGRAMMING_DATAPROCESSOR_H