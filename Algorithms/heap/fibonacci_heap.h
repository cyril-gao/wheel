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
#include <stdexcept>

#include "binary_heap.h"

namespace heap
{
    namespace details
    {
        // bidirectional cyclic list
        template <typename BCL>
        size_t length(BCL node)
        {
            size_t l = 0;
            if (node != nullptr) {
                for (BCL i = node;;) {
                    ++l;
                    assert(l < INT_MAX);
                    i = i->right;
                    if (i == node) {
                        break;
                    }
                }
            }
            return l;
        }

        template <typename T, typename C>
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

            bool is_valid() const
            {
                bool retval = (degree == length(child) && length(left) > 0);
                if (retval) {
                    if (child != nullptr) {
                        for (auto i = child;;) {
                            if (!i->is_valid() || i->parent != this) {
                                retval = false;
                                break;
                            }
                            i = i->right;
                            if (i == child) {
                                break;
                            }
                        }
                    }
                }
                return retval;
            }

            size_t count() const
            {
                size_t retval = 1;
                if (child != nullptr) {
                    for (auto i = child;;) {
                        auto r = i->count();
                        retval += r;
                        i = i->right;
                        if (i == child) {
                            break;
                        }
                    }
                }
                return retval;
            }

            bool is_child_of(Node<T, C> const* other)
            {
                if (other != nullptr) {
                    auto child = other->child;
                    if (child != nullptr) {
                        for (auto i = child;;) {
                            if (i == this && parent == other) {
                                return true;
                            }
                            i = i->right;
                            if (i == child) {
                                break;
                            }
                        }
                    }
                }
                return false;
            }
        };

        template <typename T, typename C>
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
        typename C = std::greater<T>,
        template <typename>
        class KeyTrait = details::KeyTrait
    >
    class FibonacciHeap
    {
        using key_type = typename KeyTrait<T>::key_type;
        using Node = details::Node<T, C>;

        KeyTrait<T> m_key_trait;
        std::unordered_map<key_type, Node*> m_map;
        Node * m_min;
        size_t m_size;

        bool is_valid() const
        {
            if (m_min != nullptr) {
                if (
                    m_size == m_map.size() &&
                    m_size > 0
                ) {
                    size_t sum = 0;
                    for (auto i = m_min;;) {
                        if (!i->is_valid() || i->parent != nullptr) {
                            return false;
                        }
                        sum += i->count();
                        i = i->right;
                        if (i == m_min) {
                            break;
                        }
                    }
                    return (sum == m_size);
                }
            }
            else {
                if (m_size == 0 && m_map.empty()) {
                    return true;
                }
            }
            return false;
        }

        static void detach(Node* node)
        {
            assert(node != nullptr);
            assert(node->left != node);
            auto left = node->left;
            auto right = node->right;
            left->right = right;
            right->left = left;
            node->parent = nullptr;
        #if ( defined( _DEBUG ) || defined( DEBUG ) || defined( DBG ) )
            {
                node->left = node->right = nullptr;
            }
        #endif
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

        void insert(Node* node)
        {
            assert(node != nullptr);
            if (m_min != nullptr) {
                m_min->add_sibling(node);
                if (C()(m_min->data, node->data)) {
                    m_min = node;
                }
            } else {
                node->left = node;
                node->right = node;
                m_min = node;
            }
        }

        void cut(Node* x, Node* y)
        {
            assert(x != nullptr && y != nullptr);
            assert(is_valid());
            assert(x->is_child_of(y));
            auto child = y->child;
            if (child->left != child) {
                y->child = x->right;
                detach(x);
            } else {
                assert(child == x);
                y->child = nullptr;
            }
            --y->degree;
            insert(x);
            x->parent = nullptr;
            x->mark = false;
            assert(is_valid());
        }

        void cascading_cut(Node* y)
        {
            assert(y != nullptr);
            auto z = y->parent;
            if (z != nullptr) {
                if (y->mark == false) {
                    y->mark = true;
                } else {
                    cut(y, z);
                    cascading_cut(z);
                }
            }
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
                            m_map.erase(m_key_trait.key(x->data));
                            m_map.erase(m_key_trait.key(y->data));
                            std::swap(x, y);
                            m_map[m_key_trait.key(x->data)] = x;
                            m_map[m_key_trait.key(y->data)] = y;
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
                        insert(x);
                    }
                }
                assert(is_valid());
            }
        }

        void erase(Node* to_be_deleted)
        {
            // to_be_deleted must be in the root list
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
            if (m_min == to_be_deleted) {
                m_min = to_be_deleted->right;
            }
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
            m_map.erase(m_key_trait.key(to_be_deleted->data));
            --m_size;
            consolidate();
            delete to_be_deleted;
            assert(is_valid());
        }

        void append(FibonacciHeap<T, C, KeyTrait> const& other)
        {
            for (auto i = other.m_map.begin(), ie = other.m_map.end(); i != ie; ++i) {
                insert(i->second->data);
            }
        }
    public:
        FibonacciHeap(size_t=0) : m_min(nullptr), m_size(0) {}

        void clear()
        {
            m_map.clear();
            if (m_min != nullptr) {
                auto last = m_min->left;
                last->right = nullptr;
                for (auto i = m_min; i != nullptr;) {
                    auto next = i->right;
                    details::free<T, C>(i);
                    i = next;
                }
                m_min = nullptr;
            }
        }
        ~FibonacciHeap()
        {
            clear();
        }

        FibonacciHeap(FibonacciHeap<T, C, KeyTrait> const& other) : FibonacciHeap()
        {
            append(other);
        }
        FibonacciHeap(FibonacciHeap<T, C, KeyTrait>&& other) :
            m_key_trait(std::move(other.m_key_trait)),
            m_map(std::move(other.m_map)),
            m_min(other.m_min),
            m_size(other.m_size)
        {
            other.m_min = nullptr;
            other.m_size = 0;
        }
        FibonacciHeap<T, C, KeyTrait>& operator=(FibonacciHeap<T, C, KeyTrait> const& other)
        {
            if (this != &other) {
                clear();
                append(other);
            }
        }
        FibonacciHeap<T, C, KeyTrait>& operator=(FibonacciHeap<T, C, KeyTrait>&& other)
        {
            {
                m_key_trait = std::move(other.m_key_trait);
                m_map = std::move(other.m_map);
                m_min = other.m_min;
                m_size = other.m_size;
                other.m_min = nullptr;
                other.m_size = 0;
            }
            return *this;
        }

        template <typename I>
        static FibonacciHeap<T, C, KeyTrait> make_heap(I begin, I end)
        {
            FibonacciHeap<T, C, KeyTrait> retval;
            std::for_each(begin, end, [&retval](auto const& t) { retval.insert(t); });
            return retval;
        }

        void insert(const T& t)
        {
            auto i = m_map.find(m_key_trait.key(t));
            if (i == m_map.end()) {
                auto node = new Node(t);
                m_map[m_key_trait.key(t)] = node;
                ++m_size;
                insert(node);
            }
            /* ignore
            else {
                throw std::invalid_argument("It has been inserted into the object.");
            }
            */
            assert(is_valid());
        }

        const T& minimum() const
        {
            assert(m_min != nullptr);
            return m_min->data;
        }

        void pop_min()
        {
            if (m_min != nullptr) {
                erase(m_min);
            }
        }

        FibonacciHeap<T, C, KeyTrait>& operator+=(FibonacciHeap<T, C, KeyTrait> const& other)
        {
            append(other);
            return *this;
        }

        void decrease(const T& _old, const T& _new)
        {
            if (C()(_old, _new)) {
                auto x = m_map.at(m_key_trait.key(_old));
                m_map.erase(m_key_trait.key(_old));
                x->data = _new;
                m_map[m_key_trait.key(_new)] = x;
                auto y = x->parent;
                if (y != nullptr && C()(y->data, x->data)) {
                    cut(x, y);
                    cascading_cut(y);
                }
                if (C()(m_min->data, x->data)) {
                    m_min = x;
                }
                assert(is_valid());
            } else {
                throw std::invalid_argument("new value must be less than the original one");
            }
        }

        void erase(const T& t)
        {
            auto i = m_map.find(m_key_trait.key(t));
            if (i != m_map.end()) {
                auto node = i->second;
                if (node != m_min) {
                    auto parent = node->parent;
                    if (parent != nullptr) {
                        cut(node, parent);
                    }
                    // now the node must be in the root list
                    erase(node);
                }
                else {
                    pop_min();
                }
                assert(is_valid());
            }
        }

        const T& operator[](const T& t) const
        {
            auto x = m_map.at(m_key_trait.key(t));
            return x->data;
        }

        size_t size() const
        {
            return m_size;
        }
        bool empty() const
        {
            return m_size == 0;
        }
        void swap(FibonacciHeap<T, C, KeyTrait>& other)
        {
            using std::swap;
            m_key_trait.swap(other.m_key_trait);
            m_map.swap(other.m_map);
            swap(m_min, other.m_min);
            swap(m_size, other.m_size);
        }
    };
}

#endif //FIBONACCI_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
