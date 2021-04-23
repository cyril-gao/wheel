#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>

#include <atomic>
#include <thread>
#include <vector>
#include "latch.hpp"

using namespace experimental;

int main()
{
    try {
        size_t n = std::thread::hardware_concurrency() * 8;
        std::atomic<int> count(0);
        latch l(n);
        auto task = [&]() {
            for (int i = 0; i < 100; ++i) {
                count.fetch_add(1, std::memory_order_relaxed);
                unsigned int r = rand();
                std::this_thread::sleep_for(std::chrono::milliseconds(r % 1000));
            }
            l.count_down();
        };
        std::vector<std::thread> threads;
        {
            threads.reserve(n);
            for (size_t i = 0; i < n; ++i) {
                threads.emplace_back(std::thread(task));
            }
        }
        l.wait();
        if (count.load(std::memory_order_relaxed) != 100 * n) {
            printf("A bug has been found\n");
        }
        std::for_each(std::begin(threads), std::end(threads), [](auto& t) { t.join(); });
    } catch (std::exception const & e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }

    return 0;
}
