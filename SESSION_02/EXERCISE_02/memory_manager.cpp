#include <iostream>
#include <ostream>
#include <cstdio>
#include <vector>
#include <random>

void print_max_min(const std::vector<int>& nums)
{
    auto max = nums[0];
    auto min = nums[0];
    for (auto &num : nums)
    {
        if (num > max)
        {
            max = num;
        }
        if (num < min)
        {
            min = num;
        }
    }
    std::cout << "Maximum number in array: " << max << std::endl;
    std::cout << "Minimum number in array: " << min << std::endl;
}

int main (const int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./memory_manager <size of array [1...n]>" << std::endl;
        return 1;
    }

    const auto size{strtol(argv[1], nullptr, 10)};
    std::vector v(size, 0);
    for (int &n : v)
    {
        n = std::rand();
    }

    print_max_min(v);
    return 0;
}
