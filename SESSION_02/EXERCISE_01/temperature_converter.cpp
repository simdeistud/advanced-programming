#include <iostream>
#include <string>

int main(const int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./temperature_converter <temperature> <unit [Farenheit|Celsius]>" << std::endl;
        return 1;
    }

    const auto temp{strtod(argv[1], nullptr)};
    const auto unit{std::string(argv[2])};

    if (unit == "Farenheit")
    {
        std::cout << "Converted to Farenheit: " << 9*temp/5 + 32 << std::endl;
        return 0;
    }

    if (unit == "Celsius")
    {
        std::cout << "Converted to Celsius: " << 5*(temp - 32)/9 << std::endl;
        return 0;
    }

    std::cerr << "Invalid inputs!" << std::endl;
    return 1;
}
