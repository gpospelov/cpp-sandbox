#include <iostream>
#include <cassert>
#include <string>

template<typename Key, typename Value>
class Data {
public:
    Data(Key key, Value value) : m_key(key), m_value(value) {}
    Key m_key;
    Value m_value;
    Value result() const { return m_key + m_value; }
};

template<typename Key>
class Data<Key, std::string> {
public:
    Data(Key key, std::string value) : m_key(key), m_value(value) {}
    Key m_key;
    std::string m_value;
    std::string result() const { return std::to_string(m_key) + m_value; }
};

int main() {
    Data<int, int> data(1, 2);
    assert(data.result() == 3);

    Data<int, std::string> data2(1, "A");
    assert(data2.result() == "1A");

    return 0;
}
