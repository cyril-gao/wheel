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

#include "binary_heap.h"

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

            void add_sibling(Node<T, C> * other)
            {
                assert(other != nullptr);
                assert(left != nullptr && right != nullptr);
                auto tail = left;
                tail->right = other;
                other->left = tail;
                other->right = this;
                left = other;
                other->parent = parent;
            }
        };

        template <
            typename T,
            typename C = std::greater_equal<T>
        >
        void free(Node<T, C>* node)
        {
            if (node != nullptr) {
                auto child = node->child;
                if (child != nullptr) {
                    auto last = child->left;
                    last->right = nullptr;
                    for (auto i = child; i != nullptr;) {
                        auto next = i->right;
                        free(i);
                        i = next;
                    }
                }
                delete node;
            }
        }
    }

    template <
        typename T,
        typename C = std::greater_equal<T>,
        template <typename>
        class KeyTrait = details::KeyTrait
    >
    class FibonacciHeap
    {
        using Node = details::Node<T, C>;
        Node * m_min;
        size_t m_size;

        static void detach(Node* node)
        {
            assert(node != nullptr);
            assert(node->left != node);
            auto left = node->left;
            auto right = node->right;
            left->right = right;
            right->left = left;
        }

        static void fib_heap_link(Node* y, Node* x)
        {
            assert(x != nullptr && y != nullptr);
            if (x->child != nullptr) {
                x->child->add_sibling(y);
            } else {
                x->child = y;
                y->left = y->right = y;
                y->parent = x;
            }
            ++x->degree;
            y->mark = false;
        }

        void consolidate()
        {
            if (m_size > 1 && m_min->left != m_min) {
                auto first = m_min;
                auto last = first->left;
                assert(first != last);
                last->right = nullptr;
                m_min = nullptr;
                std::vector<Node*> A(m_size, nullptr);
                for (auto* x = first; x != nullptr;) {
                    auto right = x->right;
                    x->left = x->right = x;
                    size_t d = x->degree;
                    while (A[d] != nullptr) {
                        auto* y = A[d];
                        if (C()(x->data, y->data)) {
                            std::swap(x, y);
                        };
                        fib_heap_link(y, x);
                        A[d] = nullptr;
                        ++d;
                    }
                    A[d] = x;
                    x = right;
                }

                for (auto x : A) {
                    if (x != nullptr) {
                        if (m_min != nullptr) {
                            m_min->add_sibling(x);
                            if (C()(m_min->data, x->data)) {
                                m_min = x;
                            }
                        } else {
                            m_min = x;
                            assert(m_min->left == m_min && m_min->right == m_min);
                        }
                    }
                }
            }
        }

    public:
        FibonacciHeap(size_t=0) : m_min(nullptr), m_size(0) {}
        ~FibonacciHeap()
        {
            if (m_min != nullptr) {
                auto last = m_min->left;
                last->right = nullptr;
                for (auto i = m_min; i != nullptr;) {
                    auto next = i->right;
                    details::free(i);
                    i = next;
                }
            }
        }

        FibonacciHeap(FibonacciHeap<T, C, KeyTrait> const&);
        FibonacciHeap(FibonacciHeap<T, C, KeyTrait>&&);
        FibonacciHeap<T, C, KeyTrait>& operator=(FibonacciHeap<T, C, KeyTrait> const&);
        FibonacciHeap<T, C, KeyTrait>& operator=(FibonacciHeap<T, C, KeyTrait>&&);

        template <typename I>
        static FibonacciHeap<T, C, KeyTrait> make_heap(I begin, I end)
        {
            FibonacciHeap<T, C, KeyTrait> retval;
            std::for_each(begin, end, [&retval](auto const& t) { retval.insert(t); });
            return retval;
        }

        void insert(const T& t)
        {
            auto node = new details::Node(t);
            if (m_min != nullptr) {
                m_min->add_sibling(node);
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
        void pop_min()
        {
            if (m_min != nullptr) {
                auto to_be_deleted = m_min;
                auto child = to_be_deleted->child;
                if (child != nullptr) {
                    for (auto i = child;;) {
                        i->parent = nullptr;
                        i = i->right;
                        if (i == child) {
                            break;
                        }
                    }
                }
                m_min = to_be_deleted->right;
                if (m_min != to_be_deleted) {
                    detach(to_be_deleted);
                    if (child != nullptr) {
                        auto last1 = m_min->left;
                        auto last2 = child->left;
                        last1->right = child;
                        child->left = last1;
                        last2->right = m_min;
                        m_min->left = last2;
                    }
                }
                else {
                    m_min = child;
                }
                --m_size;
                consolidate();
                delete to_be_deleted;
            }
        }

        FibonacciHeap<T, C, KeyTrait> & operator+=(FibonacciHeap<T, C, KeyTrait> const& other);

        void replace(const T& _old, const T& _new);

        void erase(const T& t);

        const T& operator[](const T& t) const;

        size_t size() const
        {
            return m_size;
        }
        bool empty() const
        {
            return m_size == 0;
        }
        void swap(FibonacciHeap<T, C, KeyTrait>& other);
    };
}

#endif //FIBONACCI_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
