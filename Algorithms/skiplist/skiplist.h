#ifndef SKIPLIST_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E
#define SKIPLIST_H_1EA09AC6_A9BB_4D0F_BB17_28ED0242C21E

#include <assert.h>
#include <stdint.h>
#include <algorithm>
#include <random>
#include <vector>
#include <memory>
#include <utility>
#include <unordered_map>


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
        Node(const Node& other) : data(other.data), previous(other.previous.size(), nullptr), next(other.next.size(), nullptr) {}
    };

    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_real_distribution<double> m_dis;
    Node m_header;
    size_t m_size;

    static void free(Node& header)
    {
        if (!header.next.empty()) {
            for (auto i = header.next[0]; i != nullptr;) {
                auto next = i->next[0];
                delete i;
                i = next;
            }
            header.next.clear();
        }
    }

    void swap(Node& header)
    {
        std::vector<Node*> next{std::move(header.next)};
        header.next = m_header.next;
        for (size_t i = header.next.size(); i > 0;) {
            --i;
            header.next[i]->previous[i] = &header;
        }
        m_header.next = std::move(next);
        for (size_t i = m_header.next.size(); i > 0;) {
            --i;
            m_header.next[i]->previous[i] = &m_header;
        }
    }

    void copy_to(Node& header) const
    {
        std::unordered_map<const Node*, Node*> map;
        try {
            header.previous = m_header.previous;
            header.next.resize(m_header.next.size());
            map[&m_header] = &header;
            for (const Node* i = m_header.next[0]; i != nullptr; i = i->next[0]) {
                std::unique_ptr<Node> new_node(new Node(*i));
                map[i] = new_node.get();
                for (size_t j = i->previous.size(); j > 0;) {
                    --j;
                    auto previous = map[i->previous[j]];
                    previous->next[j] = new_node.get();
                    new_node->previous[j] = previous;
                }
                new_node.release();
            }
        } catch (...) {
            free(header);
            throw;
        }
    }

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
        free(m_header);
    }
    Skiplist(const Skiplist<T>& other) : m_gen(m_rd()), m_dis(0, 1.0), m_size(other.m_size)
    {
        other.copy_to(m_header);
    }
    Skiplist(Skiplist<T>&& other) : m_gen(m_rd()), m_dis(0, 1.0), m_size(other.m_size)
    {
        swap(other.m_header);
        other.m_size = 0;
    }
    void swap(Skiplist<T>& other)
    {
        if (this != &other) {
            swap(other.m_header);
            std::swap(m_size, other.m_size);
        }
    }
    Skiplist& operator=(Skiplist<T> const& other)
    {
        if (this != &other) {
            free(m_header);
            other.copy_to(m_header);
            m_size = other.m_size;
        }
        return *this;
    }
    Skiplist& operator=(Skiplist<T>&& other)
    {
        if (this != &other) {
            free(m_header);
            swap(other.m_header);
            m_size = other.m_size;
            other.m_size = 0;
        }
        return *this;
    }
    bool operator==(const Skiplist<T>& other) const
    {
        bool retval = m_size == other.m_size;
        if (retval) {
            Node* i = m_header.next[0];
            Node* j = other.m_header.next[0];
            while (i != nullptr && j != nullptr && i->data == j->data) {
                i = i->next[0];
                j = j->next[0];
            }
            retval = (i == j);
        }
        return retval;
    }
    bool operator!=(const Skiplist<T>& other) const
    {
        return !operator==(other);
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
