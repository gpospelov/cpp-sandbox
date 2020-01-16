//! Parallel version of 'accumulate'.
//! (while following 'Concurrency in Action' of Anthony D. Williams)

#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <thread>

template<typename Iterator, typename T>
struct accumulate_block {
    void operator()(Iterator first, Iterator last, T& result) {
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first, last);
    if (length == 0)
        return init;

    unsigned long const min_block_size_per_thread = 100;
    unsigned long const max_threads = 1 + (length-1)/min_block_size_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const thread_count = std::min(hardware_threads!=0?hardware_threads:0, max_threads);
    unsigned long const block_size = length/thread_count;

    std::vector<T> results(thread_count);
    std::vector<std::thread> threads(thread_count-1);

    Iterator block_start = first;
    for (unsigned long i = 0; i<thread_count-1; ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);

        threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>()(block_start, last, results[thread_count-1]);

    for (auto& entry : threads)
        entry.join();

    return std::accumulate(std::begin(results), std::end(results), init);
};


int main()
{
    std::cout << "parallel-accumulate()" << "\n";
    const long length = 1002;
    std::vector<int> data(length, 1);

    std::cout << parallel_accumulate(std::begin(data), std::end(data), 0.0) << std::endl;
    return 0;
}
