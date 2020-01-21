//! Exercises with basic stl algorithms (following C++17 J. Galowicz book).
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

namespace std
{
std::ostream& operator<<(std::ostream& os, const std::pair<int, std::string>& p)
{
    return os << "(" << p.first << ", " << p.second << ")";
}
} // namespace std

template <typename InputIterator, typename OutputIterator>
OutputIterator custom_copy(InputIterator it, InputIterator it_end, OutputIterator out_it)
{
    for (; it != it_end; ++it, ++out_it)
        *out_it = *it;

    return *out_it;
}

template <typename T> void print(const T& vec)
{
    std::copy(std::begin(vec), std::end(vec),
              std::ostream_iterator<typename T::value_type>(std::cout, ","));
}

void func_copy()
{
    std::vector<std::pair<int, std::string>> vec = {{1, "one"}, {2, "two"}, {3, "three"}};
    std::map<int, std::string> map;
    std::copy(vec.begin(), vec.end(), std::inserter(map, std::begin(map)));

    auto shell_it = std::ostream_iterator<std::pair<int, std::string>>(std::cout, ",");
    custom_copy(map.begin(), map.end(), shell_it);
}

void func_copy_even_values()
{
    const std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::vector<int> v2, v3;

    auto odd_number = [](int x) { return x % 2 != 0; };
    auto even_number = [](int x) { return x % 2 == 0; };

    std::copy_if(vec.begin(), vec.end(), std::back_inserter(v2), even_number);
    std::remove_copy_if(vec.begin(), vec.end(), std::back_inserter(v3), odd_number);
    print(vec);
    print(v2);
    print(v3);
}

int main()
{
    std::cout << "stl_algorithm_basics()" << std::endl;

    func_copy();
    func_copy_even_values();

    return 0;
}
