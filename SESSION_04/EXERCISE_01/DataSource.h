//
// Created by simone on 25/10/25.
//

#ifndef ADVANCED_PROGRAMMING_DATASOURCE_H
#define ADVANCED_PROGRAMMING_DATASOURCE_H
#include <iostream>
#include <istream>
#include <string>
#include <vector>

class DataSource
{
public:
    std::string name;
    std::vector<double> data;

    DataSource(const std::string& name, const std::vector<double>& data) : name(name), data(data)
    {
    }

    virtual ~DataSource()
    {
        delete &name;
        delete &data;
    }

    void display_info() const
    {
    }

    virtual void read_data() = 0;
};

class FileDataSource : public DataSource
{
public:

    FILE * file;

    FileDataSource(const std::string& filename) : name(filename)
    {
        file = fopen(filename.c_str(), "r");
    }

    ~FileDataSource() override
    {
        fclose(file);
    }
};

class ConsoleDataSource : public DataSource
{
public:

    ConsoleDataSource()
    {
        name = "Console";
    }
};

#endif //ADVANCED_PROGRAMMING_DATASOURCE_H
