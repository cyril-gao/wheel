#include <algorithm>
#include <assert.h>
#include "merge.h"
#include "sssp.h"

std::vector<int> sssp::ShortestPaths::get_path(int vertex) const
{
    std::vector<int> tmp;
    for (int parent = edges[vertex].parent; parent >= 0;) {
        tmp.push_back(parent);
        parent = edges[parent].parent;
    }
    return std::vector<int>(tmp.rbegin(), tmp.rend());
}

float sssp::ShortestPaths::get_distance(int vertex) const
{
    return edges[vertex].distance;
}

namespace
{
    sssp::ShortestPaths initialize_single_source(sssp::Graph const& graph, int source)
    {
        size_t V = graph.size();
        sssp::ShortestPaths retval;
        retval.edges.resize(V);
        for (int i = 0; i < static_cast<int>(V); ++i) {
            retval.edges[i].vertex = i;
        }
        retval.edges[source].distance = 0;
        retval.edges[source].weight = 0;
        return retval;
    }

    bool relax(sssp::Graph const& graph, int from, int to, sssp::Edge const& input, sssp::Edge& inout)
    {
        assert(input.vertex == from && inout.vertex == to);
        bool retval = false;
        auto sum = input.distance + graph[from].at(to).weight;
        if (sum < inout.distance) {
            inout.distance = sum;
            inout.parent = from;
            inout.weight = graph[from].at(to).weight;
            retval = true;
        }
        return retval;
    }

    bool relax(sssp::Graph const& graph, int from, int to, sssp::ShortestPaths& result)
    {
        return relax(graph, from, to, result[from], result[to]);
    }
}

bool sssp::bellman_ford(Graph const& graph, int source, sssp::ShortestPaths & output)
{
    auto result = initialize_single_source(graph, source);
    for (size_t i = 1, V = graph.size(); i < V; ++i) {
        for (int u = 0; u < static_cast<int>(V); ++u) {
            std::for_each(
                graph[u].begin(), graph[u].end(),
                [=, &graph, &result](auto v) { relax(graph, u, v.first, result); }
            );
        }
    }
    output.swap(result);
    bool retval = true;
    for (int u = 0, V = static_cast<int>(graph.size()); u < V; ++u) {
        if (
            std::any_of(
                graph[u].begin(), graph[u].end(),
                [=, &graph, &output](auto v) {
                    return ((output[u].distance + graph[u].at(v.first).weight) < output[v.first].distance);
                }
            )
        ) {
            retval = false;
            break;
        }
    }
    return retval;
}

namespace
{
    void dfs(sssp::Graph const& graph, int vertex, std::vector<bool>& visited, std::vector<int> & leavers)
    {
        visited[vertex] = true;
        std::for_each(
            graph[vertex].cbegin(), graph[vertex].cend(),
            [=, &visited, &leavers](auto const& e) {
                if (!visited[e.first]) {
                    dfs(graph, e.first, visited, leavers);
                }
            }
        );
        leavers.push_back(vertex);
    }

    std::vector<int> toplogical_sort(sssp::Graph const& graph)
    {
        size_t V = graph.size();
        std::vector<bool> visited(V, false);
        std::vector<int> leavers;
        leavers.reserve(V);
        for (int i = 0; i < static_cast<int>(V); ++i) {
            if (!visited[i]) {
                dfs(graph, i, visited, leavers);
            }
        }
        return std::vector<int>(leavers.rbegin(), leavers.rend());
    }
}

sssp::ShortestPaths sssp::dag(sssp::Graph const& graph, int source)
{
    auto leavers = toplogical_sort(graph);
    int i = 0, V = static_cast<int>(leavers.size());
    while (i < V && leavers[i] != source) {
        ++i;
    }
    auto result = initialize_single_source(graph, source);
    for (; i < V; ++i) {
        int v = leavers[i];
        std::for_each(
            graph[v].cbegin(), graph[v].cend(),
            [=, &result, &graph](const auto& e) {
                relax(graph, v, e.first, result);
            }
        );
    }
    return result;
}

namespace
{
    class Indexer
    {
        using index_t = std::vector<sssp::Edge>::iterator;
        std::vector<index_t> m_map;
    public:
        Indexer(size_t V, std::vector<sssp::Edge>& vertices)
        {
            m_map.reserve(V);
            for (auto i = vertices.begin(), ie = vertices.end(); i != ie; ++i) {
                m_map.push_back(i);
            }
        }
        void set(const sssp::Edge& edge, index_t i)
        {
            m_map[edge.vertex] = i;
        }
        index_t get(int v)
        {
            return m_map[v];
        }
    };

    void rearrange(std::vector<sssp::Edge>& inout)
    {
        for (int i = 0, n = static_cast<int>(inout.size()); i < n; ++i) {
            if (inout[i].vertex != i) {
                for (auto t1 = inout[i], t2 = inout[t1.vertex];;) {
                    inout[t1.vertex] = t1;
                    if (t2.vertex != i) {
                        t1 = t2;
                        t2 = inout[t1.vertex];
                    }
                    else {
                        inout[i] = t2;
                        break;
                    }
                }
            }
        }
    }
}

sssp::ShortestPaths sssp::dijkstra(sssp::Graph const& graph, int source)
{
    auto comparator = [](const sssp::Edge& l, const sssp::Edge& r) {
        return l.distance > r.distance;
    };
    auto updating_heap = [](
        sssp::Edge const& current,
        std::vector<sssp::Edge>::iterator begin,
        std::vector<sssp::Edge>::iterator end,
        const Graph& graph,
        decltype(comparator) comparator,
        std::vector<bool>& used,
        Indexer& indexer
    ) {
        std::for_each(
            graph[current.vertex].begin(),
            graph[current.vertex].end(),
            [&](auto edge) {
                if (!used[edge.first]) {
                    if (relax(graph, current.vertex, edge.first, *indexer.get(current.vertex), *indexer.get(edge.first))) {
                        auto vertex_index = indexer.get(edge.first);
                        heap::rise(begin, end, vertex_index, comparator, &indexer);
                    }
                }
            }
        );
    };

    size_t V = graph.size();
    auto retval = initialize_single_source(graph, source);
    Indexer indexer(V, retval.edges);
    auto begin = retval.edges.begin();
    auto si = begin + source, last = begin + (V - 1);
    auto current = *si;
    indexer.set(current, last);
    indexer.set(*last, si);
    std::iter_swap(si, last);
    std::vector<bool> used(V, false);
    used[source] = true;
    updating_heap(current, begin, last, graph, comparator, used, indexer);
    for (--last; last > begin; --last) {
        current = *begin;
        indexer.set(*last, begin);
        indexer.set(*begin, last);
        std::iter_swap(begin, last);
        heap::sink(begin, last, begin, comparator, &indexer);
        updating_heap(current, begin, last, graph, comparator, used, indexer);
    }
    rearrange(retval.edges);
    return retval;
}