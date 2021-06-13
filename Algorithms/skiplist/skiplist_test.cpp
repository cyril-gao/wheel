#include <stdio.h>
#include <string.h>
#include <limits>
#include <random>
#include <vector>
#include <set>
#include <chrono>
#include <algorithm>

#include "skiplist.h"
#include "check.h"

template <typename T>
struct Operation
{
    T key;
    enum Op { INSERTING, DELETING, FINDING } opertion;

    Operation(T k = 0, Op i = INSERTING) : key(k), opertion(i) {}
};

template <typename N>
N randnum(N start, N end)
{
    assert(start <= end);
    N diff = end - start + 1;
    N r = rand();
    r %= diff;
    return r + start;
}

template <typename T>
std::vector<Operation<T>> get_hybrid_operations(std::vector<T> const& input)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    std::vector<Operation<T>> retval;
    auto upper_limit = input.size();
    retval.reserve(upper_limit);
    std::vector<T> deleting;
    decltype(upper_limit) start = 0;
    while (start < upper_limit) {
        auto end = std::min(start + 20, upper_limit);
        auto v = randnum(start, end);
        if (v == start) {
            ++v;
        }
        for (auto i = start; i < v; ++i) {
            retval.emplace_back(input[i], Operation<T>::INSERTING);
        }
        deleting.insert(deleting.end(), input.begin() + start, input.begin() + v);
        start = v;

        end = std::min(start + 60, upper_limit);
        v = randnum(start, end);
        if (v == start) {
            ++v;
        }
        for (auto i = start; i < v; ++i) {
            retval.emplace_back(input[i], Operation<T>::FINDING);
        }

        auto dl = deleting.size();
        if (dl > 0) {
            v = randnum<decltype(dl)>(0, dl);
            if (v == 0) {
                v = 1;
            }
            for (decltype(v) i = 0; i < v; ++i) {
                retval.emplace_back(deleting[i], Operation<T>::DELETING);
            }
            deleting = std::vector<T>(deleting.begin() + v, deleting.end());
        }
    }
    for (auto v : deleting) {
        retval.emplace_back(v, Operation<T>::DELETING);
    }
    return retval;
}

void set_vs_skiplist(bool testing)
{
    const size_t limit = 512 * 1024;
    int times = 100;
    if (testing) {
        times = 3;
    }
    std::vector<size_t> input;
    input.reserve(limit);
    for (size_t i = 0; i < limit; ++i) {
        input.push_back(i);
    }
    double d1 = 0, d2 = 0;
    for (int i = 0; i < times; ++i) {
        auto operations = get_hybrid_operations<size_t>(input);
        {
            auto begin = std::chrono::system_clock::now();
            std::set<size_t> list;
            for (auto const& o : operations) {
                switch (o.opertion) {
                case Operation<size_t>::INSERTING:
                    list.insert(o.key);
                    break;
                case Operation<size_t>::DELETING:
                    list.erase(o.key);
                    break;
                case Operation<size_t>::FINDING:
                {
                    auto r = list.find(o.key);
                    break;
                }
                }
            }
            auto end = std::chrono::system_clock::now();
            d1 += std::chrono::duration<double>(end - begin).count();
        }
        {
            auto begin = std::chrono::system_clock::now();
            Skiplist<size_t> list;
            for (auto const& o : operations) {
                switch (o.opertion) {
                case Operation<size_t>::INSERTING:
                    list.insert(o.key);
                    break;
                case Operation<size_t>::DELETING:
                    list.erase(o.key);
                    break;
                case Operation<size_t>::FINDING:
                    list.contains(o.key);
                    break;
                }
            }
            auto end = std::chrono::system_clock::now();
            d2 += std::chrono::duration<double>(end - begin).count();
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(std::begin(input), std::end(input), g);
    }
    printf("set: %f, skiplist: %f\n", d1, d2);
}


void skiplist_test()
{
    const size_t limit = 10000;
    std::vector<size_t> input;
    input.reserve(limit);
    for (size_t i = 0; i < limit; ++i) {
        input.push_back(i);
    }
    {
        Skiplist<size_t> list;
        for (auto n : input) {
            list.insert(n);
            examine(list.contains(n), "Skiplist::insert is failed for the argument: %zu\n", n);
        }
        for (auto n : input) {
            list.erase(n);
            examine(!list.contains(n), "Skiplist::erase is failed for the argument: %zu\n", n);
        }
    }
    {
        Skiplist<size_t> list;
        for (auto i = input.rbegin(), e = input.rend(); i != e; ++i) {
            list.insert(*i);
            examine(list.contains(*i), "Skiplist::insert is failed for the argument: %zu\n", *i);
        }
        for (auto i = input.rbegin(), e = input.rend(); i != e; ++i) {
            list.erase(*i);
            examine(!list.contains(*i), "Skiplist::erase is failed for the argument: %zu\n", *i);
        }
    }
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(std::begin(input), std::end(input), g);
        Skiplist<size_t> list;
        for (auto n : input) {
            list.insert(n);
            examine(list.contains(n), "Skiplist::insert is failed for the argument: %zu\n", n);
        }
        for (auto n : input) {
            list.erase(n);
            examine(!list.contains(n), "Skiplist::erase is failed for the argument: %zu\n", n);
        }
    }
}


int main(int argc, char* argv[])
{
    bool testing = false;
    if (argc > 1 && strcmp(argv[1], "test") == 0) {
        testing = true;
    }
    try {
        skiplist_test();
        set_vs_skiplist(testing);
        printf("OK\n");
        return 0;
    } catch (std::exception const& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }
    return 0;
}
