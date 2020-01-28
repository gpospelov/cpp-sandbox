//! Sampling large vectors (following C++17 STL Cookbook of J. Galowicz).

#include <algorithm>
#include <iostream>
#include <random>
#include <map>
#include <iomanip>

void sampling_large_vectors()
{
    std::cout << "sampling_large_vectors()" << std::endl;
    const int mean{10};
    const size_t std_dev{3};
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::normal_distribution<> gauss(mean, std_dev);

    const size_t data_points{100000};
    std::vector<int> data;
    data.reserve(data_points);
    std::generate_n(std::back_inserter(data), data_points, [&gauss, &gen]() { return gauss(gen); });

    const size_t sample_points{100};
    std::vector<int> samples;
    data.reserve(sample_points);

    std::sample(data.begin(), data.end(), std::back_inserter(samples), sample_points,
                std::mt19937{std::random_device{}()});

    std::map<int, size_t> hist;
    for (int i : samples)
        ++hist[i];

    for (const auto &[value, count] : hist)
        std::cout << std::setw(2) << value << " " << std::string(count, '*') << std::endl;

}

int main()
{
    sampling_large_vectors();
}
