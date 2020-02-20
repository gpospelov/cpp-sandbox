//! Thread safe stack (following "Concurrency in Action" by Anthony Williams).
#include <exception>
#include <iostream>
#include <memory>
#include <mutex>
#include <stack>
#include <thread>

const int total_attempts = 10000;

struct empty_stack : std::exception {
    const char* what() const noexcept { return "it happened"; }
};

template <typename T> class threadsafe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;

public:
    threadsafe_stack() {}

    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> lock(m);
        data = other.data;
    }

    threadsafe_stack& operator=(const threadsafe_stack& other) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value));
    }

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }

    void pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack();
        value = std::move(data.top());
        data.pop();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};

class Runner
{
public:
    long int on_read_sum_of_values{0};
    long int on_write_sum_of_values{0};
    threadsafe_stack<long> data;

    void reader()
    {
        static long int nreads = 0;
        while (nreads < total_attempts) {
            try {
                auto value = data.pop();
                on_read_sum_of_values += *value;
                ++nreads;
            } catch (std::exception&) {
                std::cout << "no data\n";
                continue;
            }
        }
        std::cout << "Reading done, nreads:" << nreads << " sum:" << on_read_sum_of_values << "\n";
    }

    void writer()
    {
        static long int nwrites = 0;
        while (nwrites < total_attempts) {
            const int value = 1;
            on_write_sum_of_values += value;
            data.push(value);
            ++nwrites;
        }
        std::cout << "Writing done, nwrites:" << nwrites << " sum:" << on_write_sum_of_values
                  << "\n";
    }
};

void test_threadsafe_stack()
{
    std::cout << "test_threadsafe_stack()"
              << "\n";

    Runner runner;

    std::thread write_thread(&Runner::writer, &runner);
    std::thread read_thread(&Runner::reader, &runner);
    write_thread.join();
    read_thread.join();
}

int main()
{
    test_threadsafe_stack();
    return 0;
}
