#ifndef SKIPLIST_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
#define SKIPLIST_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E

#include <assert.h>
#include <stdint.h>
#include <algorithm>
#include <random>
#include <vector>
#include <memory>
#include <utility>


template <typename T>
class Skiplist
{
    struct Node {
        T data;
        std::vector<Node*> previous;
        std::vector<Node*> next;

        explicit Node(size_t n = 1) : previous(n, nullptr), next(n, nullptr) {}
        explicit Node(T&& t, size_t n = 1) : data(std::move(t)), previous(n, nullptr), next(n, nullptr) {}
        explicit Node(T const& t, size_t n = 1) : data(t), previous(n, nullptr), next(n, nullptr) {}
    };

    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_real_distribution<double> m_dis;
    Node m_header;
    size_t m_size;

    std::pair<std::vector<Node*>, Node*> find(T const& t) const
    {
        std::vector<Node*> ancestors;
        Node* self = nullptr;
        int n = static_cast<int>(m_header.next.size());
        ancestors.reserve(n);
        Node* previous = const_cast<Node*>(&m_header);
        for (--n; n >= 0; --n) {
            Node * i = previous->next[n];
            while (i != nullptr && i->data < t) {
                previous = i;
                i = i->next[n];
            }
            ancestors.push_back(previous);
            if (i != nullptr && i->data == t) {
                self = i;
                break;
            }
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
    Skiplist() : m_gen(m_rd()), m_dis(0, 1.0), m_size(0)
    {
    }
    ~Skiplist()
    {
        for (auto i = m_header.next[0]; i != nullptr;) {
            auto next = i->next[0];
            delete i;
            i = next;
        }
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
            size_t h = 0;
            for (size_t n = log2(m_size) + 1; h < n && m_dis(m_gen) > 0.5; ++h) {}
            if (h == 0) {
                h = 1;
            }
            std::unique_ptr<Node> new_node(new Node(t, h));
            std::reverse(result.first.begin(), result.first.end());
            for (size_t i = 0, n = std::min(result.first.size(), h); i < n; ++i) {
                auto next = result.first[i]->next[i];
                new_node->next[i] = next;
                result.first[i]->next[i] = new_node.get();
                if (next != nullptr) {
                    next->previous[i] = new_node.get();
                }
                new_node->previous[i] = result.first[i];
            }
            if (size_t n = m_header.next.size(); n < h) {
                m_header.next.resize(h, new_node.get());
                for (; n < h; ++n) {
                    new_node->previous[n] = &m_header;
                }
            }
            new_node.release();
        } else {
            result.second->data = t;
        }
    }

    bool erase(T const& t)
    {
        bool retval = false;
        auto result = find(t);
        auto to_be_deleted = result.second;
        if (to_be_deleted != nullptr) {
            retval = true;
            --m_size;
            assert(to_be_deleted->next.size() == to_be_deleted->previous.size());
            for (size_t n = to_be_deleted->next.size(); n > 0;) {
                --n;
                auto previous = to_be_deleted->previous[n];
                auto next = to_be_deleted->next[n];
                if (previous != nullptr) {
                    previous->next[n] = next;
                }
                if (next != nullptr) {
                    next->previous[n] = previous;
                }
            }
            delete to_be_deleted;
        }
        return retval;
    }

    size_t size() const { return m_size; }
};

#endif // SKIPLIST_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
