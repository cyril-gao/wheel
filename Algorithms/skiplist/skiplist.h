#ifndef SKIPLIST_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
#define SKIPLIST_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E

#include <assert.h>
#include <stdint.h>
#include <algorithm>
#include <vector>
#include <memory>
#include <utility>


template <typename T>
class Skiplist
{
    struct Node {
        T data;
        std::vector<Node*> nexts;

        explicit Node(size_t n = 1) : nexts(n, nullptr) {}
        explicit Node(T&& t, size_t n = 1) : data(std::move(t)), nexts(n, nullptr) {}
        explicit Node(T const& t, size_t n = 1) : data(t), nexts(n, nullptr) {}
    };

    Node m_header;
    size_t m_size;

    std::pair<std::vector<Node*>, Node*> find(T const& t) const
    {
        std::vector<Node*> ancestors;
        Node* self = nullptr;
        int n = static_cast<int>(m_header.nexts.size());
        ancestors.reserve(n);
        Node* previous = const_cast<Node*>(&m_header);
        while (n >= 0) {
            Node * i = previous->nexts[n];
            while (i != nullptr && i->data < t) {
                previous = i;
                i = i->nexts[n];
            }
            ancestors.push_back(previous);
            if (i != nullptr && i->data == t) {
                self = i;
                break;
            }
            --n;
        }
        return std::make_pair(ancestors, self);
    }

    static size_t log2(size_t n)
    {
        assert(n > 0);
        size_t retval = 0;
        for (size_t i = 1; i < n; ++retval, i <<= 1) {}
        return retval;
    }
public:
    Skiplist() : m_size(0)
    {
        m_header.nexts.push_back(nullptr);
    }

    bool contains(T const& t) const
    {
        return find(t).second != nullptr;
    }

    void insert(T const& t)
    {
        auto result = find(t);
        if (result.second == nullptr) {
            ++m_size;
            size_t n = log2(m_size);
            std::unique_ptr<Node> new_node(new Node(t, n));
            std::reverse(result.first.begin(), result.first.end());
        } else {
            result.second->data = t;
        }
    }

    bool erase(T const& t)
    {
        bool retval = false;
        auto result = find(t);
        if (result.second != nullptr) {
            retval = true;
            --m_size;
        }
        return retval;
    }
};

#endif // SKIPLIST_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E

