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
        std::cout << "[ ";
        for (const auto d : data)
        {
            std::cout << d << " ";
        }
        std::cout << "]" << std::endl;
    }

    virtual void read_data() = 0;

    std::string name;
    std::vector<double> data;

};

class FileDataSource final : public DataSource
{
public:
    FileDataSource(const std::string& filename) : DataSource(filename, std::vector<double>())
    {
        file = std::ifstream();
    }

    ~FileDataSource() override
    {
        if (file.is_open())
            file.close();
    }

    void read_data() override
    {
        file.open(name);
        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                data.push_back(std::strtod(line.c_str(), nullptr));
            }
            file.close();
        }
        else {
            std::cerr << "Unable to open file!" << std::endl;
        }
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
        std::string line;
        while (true)
        {
            getline(std::cin, line);
            if (line.empty())
            {
               break;
            }
            data.push_back(std::strtod(line.c_str(), nullptr));
        }
    }
};

#endif //ADVANCED_PROGRAMMING_DATASOURCE_H
