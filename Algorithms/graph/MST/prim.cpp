//prim.cpp
#include <algorithm>
#include <vector>
#include <unordered_map>
#include "mst.h"

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
