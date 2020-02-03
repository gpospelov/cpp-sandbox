//! Implementing prefix tree (following C++17 STL Cookbook of J. Galowicz).

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <string>
#include <vector>

template <typename T> class trie
{
public:
    std::map<T, trie> tries;
    template <typename It> void insert(It it, It end_it)
    {
        if (it == end_it)
            return;
        tries[*it].insert(std::next(it), end_it);
    }

    void insert(const std::initializer_list<T>& il) { insert(std::begin(il), std::end(il)); }

    template <typename C> void insert(const C& container)
    {
        insert(std::begin(container), std::end(container));
    }

    void print() const
    {
        std::vector<T> v;
        print(v);
    }

    void print(std::vector<T>& vec) const
    {
        if (tries.empty()) {
            std::copy(std::begin(vec), std::end(vec), std::ostream_iterator<T>(std::cout, " "));
            std::cout << "\n";
        }
        for (const auto& entry : tries) {
            vec.push_back(entry.first);
            entry.second.print(vec);
            vec.pop_back();
        }
    }

    template <typename It>
    std::optional<std::reference_wrapper<const trie>> subtrie(It it, It end_it) const
    {
        if (it == end_it)
            return std::ref(*this);

        auto found(tries.find(*it));
        if (found == tries.end())
            return {};
        return found->second.subtrie(std::next(it), end_it);
    }

    template <typename C> auto subtrie(const C& container)
    {
        return subtrie(std::begin(container), std::end(container));
    }
};

void prefix_tree()
{
    std::cout << "prefix_tree()" << std::endl;
    trie<std::string> t;
    t.insert({"hi", "how", "are", "you"});
    t.insert({"hi", "how", "do", "you", "do"});
    t.insert({"what", "is", "that"});
    t.print();

    if (auto st = t.subtrie(std::initializer_list<std::string>{"what", "is"}))
        st->get().print();
}

int main()
{
    prefix_tree();
    return 0;
}
