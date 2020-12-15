#ifndef FIBONACCI_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
#define FIBONACCI_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00

#include <stdint.h>
#include <assert.h>

#include <utility>
#include <memory>
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

            Node(const T& t) :
                data(t),
                degree(0),
                mark(false),
                parent(nullptr),
                child(nullptr),
                left(nullptr),
                right(nullptr)
            {
            }
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
        details::Node * m_min;
        size_t m_size;

        void fib_heap_link(Node* y, Node* x)
        {

        }

        void consolidate()
        {
            if (m_size > 1) {
                std::vector<Node*> A(m_size + 1, nullptr);
                for (Node* first = m_min, * x = first;;) {
                    size_t d = x->degree;
                    while (A[d] != nullptr) {
                        Node* y = A[d];
                        if (C()(x->data, y->data)) {
                            std::swap(x, y);
                        };
                    }
                }
            }
        }
    public:
        FibonacciHeap(size_t n=0);
        FibonacciHeap(FibonacciHeap<T, C, KeyTrait> const&) = default;
        FibonacciHeap(FibonacciHeap<T, C, KeyTrait>&&) = default;
        FibonacciHeap<T, C, KeyTrait>& operator=(FibonacciHeap<T, C, KeyTrait> const&) = default;
        FibonacciHeap<T, C, KeyTrait>& operator=(FibonacciHeap<T, C, KeyTrait>&&) = default;

        template <typename I>
        static FibonacciHeap<T, C, KeyTrait> make_heap(I begin, I end);

        void insert(const T& t)
        {
            auto node = new details::Node(t);
            if (m_min != nullptr) {
                details::Node * previous = m_min.left;
                previous->right = node;
                node->left = previous;
                node->right = m_min;
                m_min->left = node;
                if (C()(m_min->data, t)) {
                    m_min = node;
                }
            } else {
                node->left = node;
                node->right = node;
                m_min = node;
            }
            ++m_size;
        }

        const T& minimum() const
        {
            assert(m_min != nullptr);
            return m_min->data;
        }
        void pop_min();

        FibonacciHeap<T, C, KeyTrait> & operator+=(FibonacciHeap<T, C, KeyTrait> const& other);

        void replace(const T& _old, const T& _new);

        void erase(const T& t);

        size_t size() const
        {
            return m_min != nullptr ? m_min->degree : 0;
        }
        bool empty() const
        {
            return m_min == nullptr || m_min->degree == 0;
        }
        void swap(FibonacciHeap<T, C, KeyTrait>& other);
    };
}

#endif //FIBONACCI_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
