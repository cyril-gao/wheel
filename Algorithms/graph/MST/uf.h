#ifndef UNION_FIND_GYM_H
#define UNION_FIND_GYM_H

#include <assert.h>
#include <vector>

namespace uf
{
    class UF
    {
    public:
        virtual ~UF() = default;
        virtual void connect(size_t p, size_t q) = 0;
        virtual size_t find(size_t p) const = 0;
        virtual bool connected(size_t p, size_t q) const = 0;
        virtual size_t count() const = 0;
    };

    class ArrayBasedUF : public UF
    {
        mutable size_t m_count;
        mutable std::vector<size_t> m_ancestors;
        mutable std::vector<size_t> m_sizes;

        size_t get_parent(size_t n) const
        {
            assert(n < m_ancestors.size());
            size_t p = m_ancestors[n];
            while (p != n) {
                n = p;
                p = m_ancestors[n];
            }
            return p;
        }

    public:
        ArrayBasedUF(size_t n) : m_count(n), m_ancestors(n), m_sizes(n, 1)
        {
            for (size_t i = 0; i < n; ++i) {
                m_ancestors[i] = i;
            }
        }

        void connect(size_t p, size_t q) override
        {
            if (p != q) {
                size_t pp = get_parent(p);
                size_t qp = get_parent(q);
                if (pp != qp) {
                    size_t ps = m_sizes[pp];
                    size_t qs = m_sizes[qp];
                    if (ps < qs) {
                        m_ancestors[pp] = qp;
                        m_sizes[qp] += ps;
                    }
                    else {
                        m_ancestors[qp] = pp;
                        m_sizes[pp] += qs;
                    }
                    --m_count;
                }
            }
        }

        size_t find(size_t p) const override
        {
            return get_parent(p);
        }

        bool connected(size_t p, size_t q) const override
        {
            return get_parent(p) == get_parent(q);
        }

        size_t count() const override
        {
            return m_count;
        }
    };
}

#endif