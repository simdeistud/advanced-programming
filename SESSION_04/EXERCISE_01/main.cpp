//
// Created by simone on 25/10/25.
//

#include "DataSource.h"

int main()
{
    DataSource* fileTest = new FileDataSource("data.txt");
    fileTest->display_info();
    fileTest->read_data();
    fileTest->display_info();

    DataSource* consoleTest = new ConsoleDataSource();
    consoleTest->display_info();
    consoleTest->read_data();
    consoleTest->display_info();
    return 0;
}