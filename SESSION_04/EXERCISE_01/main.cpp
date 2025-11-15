//
// Created by simone on 25/10/25.
//

#include "DataSource.h"
#include "DataTransformer.h"

int main()
{
    DataSource* fileTest = new FileDataSource("data.txt");
    fileTest->read_data();
    std::cout << "Original data :" << std::endl;
    fileTest->display_info();
    delete fileTest;

    //DataSource* consoleTest = new ConsoleDataSource();
    //consoleTest->display_info();
    //consoleTest->read_data();
    //consoleTest->display_info();

    fileTest = new FileDataSource("data.txt");
    fileTest->read_data();
    DataTransformer* dataTransformer = new LinearScaler(fileTest, 10.0);
    dataTransformer->transform();
    delete dataTransformer;
    std::cout << "Linear transformer with f=10 :" << std::endl;
    fileTest->display_info();
    delete fileTest;

    fileTest = new FileDataSource("data.txt");
    fileTest->read_data();
    dataTransformer = new LogTransformer(fileTest);
    dataTransformer->transform();
    delete dataTransformer;
    std::cout << "Log10 transformer :" << std::endl;
    fileTest->display_info();
    delete fileTest;

    fileTest = new FileDataSource("data.txt");
    fileTest->read_data();
    dataTransformer = new StandardScaler(fileTest);
    dataTransformer->transform();
    delete dataTransformer;
    std::cout << "Standard scaling between [0,1] :" << std::endl;
    fileTest->display_info();
    delete fileTest;

    return 0;
}
