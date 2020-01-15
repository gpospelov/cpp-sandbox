//! Exercises with lambda (following C++17 J. Galowicz book).
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>

static bool begins_with_a(const std::string& str)
{
    return str.find("a") != std::string::npos;
}

static bool ends_with_b(const std::string& str)
{
    return str.rfind("b") != std::string::npos;
}

template <typename A, typename B, typename F> auto combine(F binary_func, A f1, B f2)
{
    return [=](auto param) { return binary_func(f1(param), f2(param)); };
}

void logical_conjunction()
{
    std::cout << "logical_conjunction() >" << std::endl;
    auto a_and_b(combine(std::logical_and<>{}, begins_with_a, ends_with_b));

    std::copy_if(std::istream_iterator<std::string>{std::cin}, {},
                 std::ostream_iterator<std::string>{std::cout, ", "}, a_and_b);
    std::cout << "\n";
}

int main()
{
    logical_conjunction();

    return 0;
}
