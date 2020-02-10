//! Exercises with basic stl algorithms (following C++17 J. Galowicz book).
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

template <typename It> std::tuple<It, char, int> occurencies(It it, It it_end)
{
    char c{*it};
    auto it_res = find_if(it, it_end, [c](auto cc) { return cc != c; });
    return {it_res, c, std::distance(it, it_res)};
}

std::string compress(const std::string& input)
{
    std::ostringstream oss;
    auto it = input.begin();
    while (it != input.end()) {
        auto [it_res, c, count] = occurencies(it, input.end());
        oss << c << count;
        it = it_res;
    }
    return oss.str();
}

std::string decompress(const std::string& input)
{
    std::ostringstream oss;
    std::istringstream iss(input);
    char c;
    size_t count(0);
    while (iss >> c >> count)
        oss << std::string(count, c);

    return oss.str();
}

void test_compress_decompress()
{
    std::string input{"aaabb"};
    std::cout << compress(input) << std::endl;
    std::cout << decompress("a3b2") << std::endl;
}

int main()
{
    test_compress_decompress();
    return 0;
}
