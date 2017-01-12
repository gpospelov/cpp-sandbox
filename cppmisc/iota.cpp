#include <numeric>
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <iterator>

int main()
{
    std::list<int> l(4);

    const int starting_value{0};
    std::iota(l.begin(), l.end(), starting_value);

    std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    assert(l.size() == 4);
    assert(l.front() == starting_value);
    assert(l.back() == l.size() - 1);

    std::vector<std::list<int>::iterator> v(4);
    std::iota(v.begin(), v.end(), l.begin());
    assert(*v.front() == l.front());
    assert(*v.back() == l.back());

    return 0;
}
