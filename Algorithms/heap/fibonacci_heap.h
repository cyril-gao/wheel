#ifndef FIBONACCI_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
#define FIBONACCI_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00

#include <stdint.h>
#include <assert.h>

#include <algorithm>
#include <functional>
#include <iterator>
#include <type_traits>
#include <vector>
#include <unordered_map>

namespace heap
{
    namespace details
    {
        template <
            typename T,
            typename C = std::greater_equal<T>
        >
        struct Node
        {
            T data;
            size_t degree;
            bool mark;
            Node<T, C> * parent;
            Node<T, C> * child;
            Node<T, C> * left;
            Node<T, C> * right;
        };
    }

    template <
        typename T,
        typename C = std::greater_equal<T>,
        template <typename>
        class KeyTrait = details::KeyTrait
    >
    class FibonacciHeap
    {
    public:
        FibonacciHeap(size_t n=0);
        FibonacciHeap(FibonacciHeap<T, C, KeyTrait> const&) = default;
        FibonacciHeap(FibonacciHeap<T, C, KeyTrait>&&) = default;
        FibonacciHeap<T, C, KeyTrait>& operator=(FibonacciHeap<T, C, KeyTrait> const&) = default;
        FibonacciHeap<T, C, KeyTrait>& operator=(FibonacciHeap<T, C, KeyTrait>&&) = default;

        template <typename I>
        static FibonacciHeap<T, C, KeyTrait> make_heap(I begin, I end);

        void insert(const T& t);

        const T& minimum() const;
        void pop_min();

        FibonacciHeap<T, C, KeyTrait> & operator+=(FibonacciHeap<T, C, KeyTrait> const& other);

        void replace(const T& _old, const T& _new);

        void erase(const T& t);

        size_t size() const;
        bool empty() const;
        void swap(FibonacciHeap<T, C, KeyTrait>& other);
    };
}

#endif //FIBONACCI_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
