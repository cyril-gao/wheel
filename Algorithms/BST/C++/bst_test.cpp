#if (defined(_WIN32) || defined(_WIN64))
#include <Windows.h>
#include <psapi.h>
#undef min
#undef max
#endif

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include <limits>
#include <random>
#include <vector>
#include <set>
#include <chrono>
#include <algorithm>
#include "check.h"
#include "rbtree.h"
#include "avltree.h"

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
        for (auto i = start, ie = std::min(v, upper_limit); i < ie; ++i) {
            retval.emplace_back(input[i], Operation<T>::INSERTING);
        }
        deleting.insert(deleting.end(), input.begin() + start, input.begin() + v);
        start = v;

        end = std::min(start + 60, upper_limit);
        v = randnum(start, end);
        if (v == start) {
            ++v;
        }
        for (auto i = start, ie = std::min(v, upper_limit); i < ie; ++i) {
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

template <template <typename> class BST>
void set_vs_bst(bool testing)
{
    const size_t limit = 1000000;
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
            std::set<size_t> tree;
            for (auto const& o : operations) {
                switch (o.opertion) {
                case Operation<size_t>::INSERTING:
                    tree.insert(o.key);
                    break;
                case Operation<size_t>::DELETING:
                    tree.erase(o.key);
                    break;
                case Operation<size_t>::FINDING:
                    {
                        auto r = tree.find(o.key);
                        break;
                    }
                }
            }
            auto end = std::chrono::system_clock::now();
            d1 += std::chrono::duration<double>(end - begin).count();
        }
        {
            auto begin = std::chrono::system_clock::now();
            BST<size_t> tree;
            for (auto const& o : operations) {
                switch (o.opertion) {
                case Operation<size_t>::INSERTING:
                    tree.insert(o.key);
                    break;
                case Operation<size_t>::DELETING:
                    tree.erase(o.key);
                    break;
                case Operation<size_t>::FINDING:
                    tree.contains(o.key);
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
    printf("std: %f, mine: %f (%4.2f%%)\n", d1, d2, (d2/d1) * 100);
}

template <template <typename> class BST>
void tree_test()
{
    const size_t limit = 10000;
    std::vector<size_t> input;
    input.reserve(limit);
    for (size_t i = 0; i < limit; ++i) {
        input.push_back(i);
    }
    {
        BST<size_t> tree;
        for (auto n : input) {
            tree.insert(n);
            examine(tree.valid(), "after inserting %zu, the tree is illegal\n", n);
        }
        {
            BST<size_t> other(tree);
            examine(tree == other, "copy constructor is failed\n");
        }
        for (auto n : input) {
            tree.erase(n);
            examine(tree.valid(), "after removing %zu, the tree is illegal\n", n);
        }
    }
    {
        BST<size_t> tree;
        for (auto i = input.rbegin(), e = input.rend(); i != e; ++i) {
            tree.insert(*i);
            examine(tree.valid(), "after inserting %zu, the tree is illegal\n", *i);
        }
        {
            BST<size_t> other(tree);
            examine(tree == other, "copy constructor is failed\n");
        }
        for (auto i = input.rbegin(), e = input.rend(); i != e; ++i) {
            tree.erase(*i);
            examine(tree.valid(), "after removing %zu, the tree is illegal\n", *i);
        }
    }
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(std::begin(input), std::end(input), g);
        BST<size_t> tree;
        for (auto n : input) {
            tree.insert(n);
            examine(tree.valid(), "after inserting %zu, the tree is illegal\n", n);
        }
        {
            BST<size_t> other(tree);
            examine(tree == other, "copy constructor is failed\n");
            BST<size_t> third(std::move(other));
            examine(tree != other, "move constructor is failed\n");
            examine(tree == third, "move constructor is failed\n");
            for (auto n : input) {
                third.erase(n);
                examine(third.valid(), "after removing %zu, the tree is illegal\n", n);
            }
        }
        for (auto n : input) {
            tree.erase(n);
            examine(tree.valid(), "after removing %zu, the tree is illegal\n", n);
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
        tree_test<RedBlackTree>();
        tree_test<AVLTree>();
        set_vs_bst<RedBlackTree>(testing);
        set_vs_bst<AVLTree>(testing);
        printf("OK\n");
        return 0;
    } catch (std::exception const& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }
}
