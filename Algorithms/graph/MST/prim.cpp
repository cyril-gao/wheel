//prim.cpp
#include <algorithm>
#include <vector>
#include <unordered_map>
#include "mst.h"
#if 0
#include "merge.h"
#else
#include <kary_heap.h>
#endif

#if 0
namespace
{
    class Indexer
    {
        using index_t = std::vector<mst::Edge>::iterator;
        //std::unordered_map<int, index_t> m_map;
        std::vector<index_t> m_map;
    public:
        Indexer(size_t V, std::vector<mst::Edge> & vertices)
        {
            m_map.reserve(V);
            for (auto i = vertices.begin(), ie = vertices.end(); i != ie; ++i) {
                m_map.push_back(i);
            }
            /*
            for (int i = 0; i < static_cast<int>(V); ++i) {
                m_map[i] = vertices.begin() + i;
            }
            */
        }
        void set(const mst::Edge & edge, index_t i)
        {
            m_map[edge.vertex] = i;
        }
        index_t get(int v)
        {
            return m_map[v];
        }
        void erase(int v)
        {
            //m_map.erase(v);
        }
    };        
}

mst::MST mst::prim(const Graph& graph)
{
    mst::MST retval;
    auto comparator = [](const mst::Edge & l, const mst::Edge & r) {
        return l.weight > r.weight;
    };
    auto updating_heap = [](
        mst::Edge const& current,
        std::vector<mst::Edge>::iterator begin,
        std::vector<mst::Edge>::iterator end,
        const Graph& graph,
        decltype(comparator) comparator,
        std::vector<bool>& used,
        Indexer& indexer
    ) {
        std::for_each(
            graph[current.vertex].begin(),
            graph[current.vertex].end(),
            [&](Graph::Edge edge) {
                if (!used[edge.vertex]) {
                    auto vertex_index = indexer.get(edge.vertex);
                    if (edge.weight < vertex_index->weight) {
                        vertex_index->parent = current.vertex;
                        vertex_index->path_weight = current.path_weight + edge.weight;
                        vertex_index->weight = edge.weight;
                        heap::rise(begin, end, vertex_index, comparator, &indexer);
                    }
                }
            }
        );
    };

    size_t V = graph.size();
    retval.edges.reserve(V - 1);
    std::vector<bool> used(V, false);
    std::vector<mst::Edge> vertices(V);
    for (int i = 0; i < static_cast<int>(V); ++i) {
        vertices[i].vertex = i;
    }
    vertices[0].weight = 0;
    vertices[0].path_weight = 0;
    Indexer indexer(V, vertices);
    auto current = vertices[0];
    auto begin = vertices.begin();
    auto last = begin + V - 1;
    used[0] = true;
    *begin = *last;
    indexer.set(*begin, begin);
    updating_heap(current, begin, last, graph, comparator, used, indexer);
    for (--last; begin < last; --last) {
        current = vertices[0];
        used[current.vertex] = true;
        *begin = *last;
        indexer.set(*begin, begin);
        heap::sink(begin, last, begin, comparator, &indexer);
        updating_heap(current, begin, last, graph, comparator, used, indexer);
        retval.weight += current.weight;
        retval.edges.emplace_back(current);
    }
    retval.weight += begin->weight;
    retval.edges.emplace_back(*begin);
    return retval;
}

#else

namespace
{
    template <typename T>
    struct KeyTrait;

    template <>
    struct KeyTrait<mst::Edge>
    {
        using key_type = int;
        key_type key(const mst::Edge& t) const { return t.vertex; }
        void swap(KeyTrait<mst::Edge>&) {}
    };
}

mst::MST mst::prim(const Graph& graph)
{
    auto V = graph.size();
    mst::MST retval(V);

    auto comparator = [](const mst::Edge& l, const mst::Edge& r) {
        return l.weight > r.weight;
    };

    heap::KaryHeap<16, mst::Edge, decltype(comparator), KeyTrait> kary_heap;
    kary_heap.insert(mst::Edge{ 0, 0 });
    for (int i = 1, e = static_cast<int>(V); i < e; ++i) {
        kary_heap.insert(mst::Edge{ i });
    }
    std::vector<bool> visited(V, false);
    while (!kary_heap.empty()) {
        auto u = kary_heap.minimum();
        kary_heap.pop_min();
        visited[u.vertex] = true;
        retval.weight += u.weight;
        u.path_weight = retval.weight;
        retval.edges[u.vertex] = u;

        std::for_each(
            graph.adj(u.vertex).begin(),
            graph.adj(u.vertex).end(),
            [uv = u.vertex, &visited, &kary_heap](auto v) {
                if (!visited[v.vertex]) {
                    mst::Edge ve{ v.vertex };
                    decltype(auto) old = kary_heap[ve];
                    if (old.weight > v.weight) {
                        ve.parent = uv;
                        ve.weight = v.weight;
                        kary_heap.decrease(old, ve);
                    }
                }
            }
        );
    }
    return retval;
}

#endif
