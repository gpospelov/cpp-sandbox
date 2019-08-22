//! Example of Haskel like function concatenation, while following C++17 J. Galowicz book.
#include <iostream>

template <typename A, typename B, typename C> auto concatenate(A a, B b, C c)
{
    return [=](auto... params) { return a(b(c(params...))); };
}

template <typename T, typename... Ts> auto concatenate2(T t, Ts... ts)
{
    if constexpr (sizeof...(ts) > 0) {
        return [=](auto... params) { return t(concatenate2(ts...)(params...)); };
    } else {
        return [=](auto... params) { return t(params...); };
    }
}

int main()
{
    std::cout << "Concatenate functions" << std::endl;

    auto twice = [](int i) { return i * 2; };
    auto thrice = [](int i) { return i * 3; };

    auto combined = concatenate(twice, thrice, std::plus<int>{});
    std::cout << combined(1, 2) << "\n";

    auto combined2 = concatenate2(twice, thrice, std::plus<int>{});
    std::cout << combined2(1, 2) << "\n";

    return 0;
}
