// While reading "Practical C++ metaprogramming" ...
#include <iostream>
#include <cassert>
#include <tuple>

class Data {
public:
    Data(int x, int y) : m_x(x), m_y(y) {}
    double x() const { return m_x; }
    double y() const { return m_y; }
private:
    int m_x;
    int m_y;
};

template<typename FirstValue, typename SecondValue>
int sum_values(FirstValue value1, SecondValue value2) {
    return value1()+value2();
}

int fun(int *value) {
    return *value;
}

template <typename F>
struct make_tuple_of_params;

template <typename Ret, typename... Args>
struct make_tuple_of_params<Ret (Args...)>
{
    using type = std::tuple<Args...>;
};

template <typename F> using make_tuple_of_params_t = typename make_tuple_of_params<F>::type;

int main()
{
    // lambdas as template parameters
    Data data(1,2);
    int result = sum_values([&](){return data.x();}, [&](){return data.y();});
    assert(result == 3);

    // adding pointer to the type
    int x{1};
    std::add_pointer<int>::type y;
    *y = x;
    assert(fun(y) == 1.0);

    // making tuple from list of function parameters
    bool is_same_type =
            std::is_same<make_tuple_of_params_t<void(int, double)>, std::tuple<int, double>>::value;
    assert(is_same_type);

    return 0;
}
