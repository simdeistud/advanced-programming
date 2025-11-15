//
// Created by simone on 25/10/25.
//

#ifndef ADVANCED_PROGRAMMING_DATASOURCE_H
#define ADVANCED_PROGRAMMING_DATASOURCE_H
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>


class DataSource
{
public:

    DataSource(const std::string& name, const std::vector<double>& data) : name(name), data(data)
    {
    }

    virtual ~DataSource() = default;

    void display_info() const
    {
    }

    virtual void read_data() = 0;

protected:
    std::string name;
    std::vector<double> data;
};

class FileDataSource final : public DataSource
{
public:
    FileDataSource(const std::string& filename) : DataSource(filename, std::vector<double>())
    {
        file = std::ifstream(filename);
    }

    ~FileDataSource() override
    {
        file.close();
    }

    void read_data() override
    {

    }

private:
    std::ifstream file;

};

class ConsoleDataSource final : public DataSource
{
public:

    ConsoleDataSource() : DataSource("Console", std::vector<double>())
    {
    }

    void read_data() override
    {

    }
};

#endif //ADVANCED_PROGRAMMING_DATASOURCE_H
