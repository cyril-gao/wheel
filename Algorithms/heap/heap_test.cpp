#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "binary_heap.h"
#include "kary_heap.h"
#include "fibonacci_heap.h"
#include "check.h"

void fibonacci_heap_test()
{
    heap::FibonacciHeap<int> fh;
    fh.insert(1);
    fh.insert(2);
    fh.insert(3);
    auto m = fh.minimum();
    examine(m == 1, "FibonacciHeap is failed at the line: %d\n", __LINE__);
    fh.pop_min();
    m = fh.minimum();
    examine(m == 2, "FibonacciHeap is failed at the line: %d\n", __LINE__);
    fh.pop_min();
    m = fh.minimum();
    examine(m == 3, "FibonacciHeap is failed at the line: %d\n", __LINE__);
    fh.pop_min();
    examine(fh.empty(), "FibonacciHeap is failed at the line: %d\n", __LINE__);
}

template <typename H>
void heap_test_case1(H& h)
{
    h.insert(0);
    h.insert(4);
    h.insert(-1);
    h.insert(-2);
    h.insert(-10);
    h.erase(-2);
    h.erase(-10);
    examine(h.minimum() == -1, "failed at the line: %d\n", __LINE__);
    h.pop_min();
    h.replace(4, -20);
    h.insert(-11);
    h.insert(-100);
    h.insert(-101);
    h.insert(-102);
    h.insert(-103);
    h.insert(-104);
    h.replace(-104, -12);
    examine(h.minimum() == -103, "failed at the line: %d\n", __LINE__);
    h.pop_min();
    examine(h.minimum() == -102, "failed at the line: %d\n", __LINE__);
    h.pop_min();
    h.replace(-101, 100);
    h.erase(-100);
    examine(h.minimum() == -20, "failed at the line: %d\n", __LINE__);
    h.pop_min();
    examine(h.minimum() == -12, "failed at the line: %d\n", __LINE__);
    h.pop_min();
    examine(h.minimum() == -11, "failed at the line: %d\n", __LINE__);
    h.pop_min();
    examine(h.minimum() == 0, "failed at the line: %d\n", __LINE__);
    h.pop_min();
    examine(h.minimum() == 100, "failed at the line: %d\n", __LINE__);
    h.pop_min();
    examine(h.empty(), "failed at the line: %d\n", __LINE__);
}

template <typename H>
void heap_test_case2()
{
    std::vector<int> input = { 9, 13, 6, 1, -10, 2, 8, 2, -14, -7, 9, -10, -13, 4, 0, 3, 5, 6, 7, 8 };
    auto h = H::make_heap(input.begin(), input.end());
    std::vector<int> result = { -14, -13, -10, -7, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 13 };
    for (auto r : result) {
        examine(h.minimum() == r, "failed for the input: %d\n", r);
        h.pop_min();
    }
}

template <typename H>
void heap_test_case3()
{
    std::vector<int> input1 = { 9, 13, 6, 1, -10, 2, 8, 2, -14, -7, 9, -10, -13, 4, 0, 3, 5, 6, 7, 8 };
    auto h = H::make_heap(input1.begin(), input1.end());
    std::vector<int> input2 = { 10, 11, 12, -6, -5, -4, -3, -2, -1 };
    auto h2 = H::make_heap(input2.begin(), input2.end());
    h += h2;

    std::vector<int> result = { -14, -13, -10, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    for (auto r : result) {
        examine(h.minimum() == r, "failed for the input: %d\n", r);
        h.pop_min();
    }
}

int main()
{
    {
        fibonacci_heap_test();
    }
    {
        heap::BinaryHeap<int> bh;
        heap_test_case1(bh);
        heap_test_case2<heap::BinaryHeap<int>>();
        heap_test_case3<heap::BinaryHeap<int>>();
    }

    {
        using FaryHeap = heap::KaryHeap<4, int>;
        FaryHeap fh;
        heap_test_case1(fh);
        heap_test_case2<FaryHeap>();
        heap_test_case3<FaryHeap>();
    }

    {
        using EaryHeap = heap::KaryHeap<8, int>;
        EaryHeap eh;
        heap_test_case1(eh);
        heap_test_case2<EaryHeap>();
        heap_test_case3<EaryHeap>();
    }
    return 0;
}