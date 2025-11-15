//
// Created by simone on 15/11/25.
//

#ifndef ADVANCED_PROGRAMMING_DATATRANSFORMER_H
#define ADVANCED_PROGRAMMING_DATATRANSFORMER_H
#include <algorithm>
#include <complex>

#include "DataSource.h"

class DataTransformer
{
public:
    DataTransformer(DataSource* data_source) : dataSource(data_source) {}

    virtual ~DataTransformer() = default; // The destroyer doesn't deallocate the data because its job is just to oeprate on it

    void virtual transform() = 0;

protected:
    DataSource* dataSource;
};

class LinearScaler : public DataTransformer
{
public:
    LinearScaler(DataSource* data_source, const double factor) : DataTransformer(data_source), factor(factor) {}

    void transform() override
    {
        for (auto& d : dataSource->data)
        {
            d *= factor;
        }
    }

private:
    const double factor;
};

class LogTransformer : public DataTransformer
{
public:
    LogTransformer(DataSource* data_source) : DataTransformer(data_source) {}

    void transform() override
    {
        for (auto& d : dataSource->data)
        {
            d = d <= 0 ? 0 : std::log10(d);
        }
    }
};

class StandardScaler : public DataTransformer
{
public:
    StandardScaler(DataSource* data_source) : DataTransformer(data_source) {}

    void transform() override
    {
        const auto max = *std::max_element(dataSource->data.begin(), dataSource->data.end());
        const auto min = *std::min_element(dataSource->data.begin(), dataSource->data.end());
        for (auto& d : dataSource->data)
        {
            d = (d - min) / (max - min);
        }
    }

};

#endif //ADVANCED_PROGRAMMING_DATATRANSFORMER_H