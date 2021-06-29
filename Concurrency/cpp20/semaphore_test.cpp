#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>

#include <thread>
#include <mutex>
#include <vector>
#include "semaphore.hpp"

using namespace experimental;
using namespace std::chrono_literals;

extern void test_error_handling();

void output(size_t tid, int r, std::mutex& m)
{
    int s = static_cast<int>(static_cast<int64_t>(time(nullptr)) % 100);
    std::lock_guard<std::mutex> guard(m);
    printf("Thread: %3zu: %3d -> %d\n", tid, s, r);
}

int main()
{
    try {
        size_t n = std::thread::hardware_concurrency();
        ptrdiff_t desired = 5;
        counting_semaphore sema(desired);
        std::mutex m;
        auto task = [&](size_t tid) {
            for (int i = 0; i < 10; ++i) {
            #if 0
                sema.acquire();
                output(tid, rand(), m);
                sema.release();
                std::this_thread::sleep_for(1s);
            #else
                //if (sema.try_acquire_for(2s)) {
                if (sema.try_acquire_until(std::chrono::steady_clock::now() + 10s)) {
                    output(tid, rand(), m);
                    sema.release();
                }
            #endif
            }
        };
        std::vector<std::jthread> threads;
        {
            threads.reserve(n);
            for (size_t i = 0; i < n; ++i) {
                threads.emplace_back(task, i);
            }
        }
    } catch (std::exception const & e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }
    return 0;
}
