//
// Created by simone on 25/10/25.
//

#include "DataSource.h"
#include "DataTransformer.h"

int main()
{
    DataSource* ds = nullptr;
    DataTransformer* dt = nullptr;
    std::cout << "Do you want to read from a file or from the console? [F/C] : ";
    std::string in;
    std::cin >> in;
    if (in == "F")
    {
        ds = new FileDataSource("data.txt");
    }
    if (in == "C")
    {
        ds = new ConsoleDataSource();
    }
    if (ds == nullptr) return 1;
    ds->read_data();

    std::cout << "What transformer do you want to use? [LIN/LOG/STD] : ";
    std::cin >> in;
    if (in == "LIN")
    {
        std::cout << "With which factor? : ";
        std::cin >> in;
        dt = new LinearScaler(ds, strtod(in.c_str(), nullptr));
    }
    if (in == "LOG")
    {
        dt = new LogTransformer(ds);
    }
    if (in == "STD")
    {
        dt = new StandardScaler(ds);
    }
    if (dt == nullptr) return 1;

    std::cout << "Input data : " << std::endl;
    ds->display_info();

    std::cout << "Transformed data : " << std::endl;
    dt->transform();
    ds->display_info();

    delete ds;
    delete dt;

    return 0;
}
