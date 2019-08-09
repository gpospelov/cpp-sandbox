// While following N. Josuttis talk
// String views.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <string_view>


void sort_string()
{
    const int elementCount{10};
    std::vector<std::string> coll;
    coll.reserve(elementCount);

    for(size_t i=0; i<elementCount/2; ++i) {
        coll.emplace_back("id"+std::to_string(i));
        coll.emplace_back("ID"+std::to_string(i));
    }

    auto print = [](const auto& vec) {
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    };

    std::sort(coll.begin(), coll.end());
    print(coll);

    auto sort_criteria = [](const auto& a, const auto& b){
        return std::string_view{a}.substr(2) < std::string_view{b}.substr(2);
    };
    std::sort(coll.begin(), coll.end(), sort_criteria);
    print(coll);

}


int main()
{
    sort_string();
    return 0;
}
