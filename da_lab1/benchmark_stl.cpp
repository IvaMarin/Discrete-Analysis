#include <iostream>
#include <chrono>
#include <cassert> // для функции assert
#include <algorithm>
#include <string>
#include "vector.hpp"

using duration_t = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

/*
using duration_t = std::chrono::milliseconds;
const std::string DURATION_PREFIX = "ms";
*/


int main()
{
    vector::Vector<Pair> input_stl;
    int key;
    std::string value;
    while (std::cin >> key >> value)
    {
        input_stl.push_back( Pair(key, value) );
    }

    std::cout << "Count of lines is " << input_stl.size() << std::endl;


    // Измеряем время работы stl сортировки.
    std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();
    std::stable_sort(std::begin(input_stl), std::end(input_stl));
    auto end_ts = std::chrono::system_clock::now();
    uint64_t stl_sort_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();

    std::cout << "STL stable sort time: " << stl_sort_ts << DURATION_PREFIX << std::endl;
}

