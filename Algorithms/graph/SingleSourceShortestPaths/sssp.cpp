#include <assert.h>
#include <algorithm>
#include <kary_heap.h>
#include "sssp.h"

std::vector<int> sssp::ShortestPaths::get_path(int vertex) const
{
    std::vector<int> tmp;
    while (vertex >= 0) {
        tmp.push_back(vertex);
        vertex = edges[vertex].parent;
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

    bool relax(double weight, sssp::Edge const& from, sssp::Edge& to)
    {
        bool retval = false;
        auto sum = from.distance + weight;
        if (sum < to.distance) {
            to.distance = sum;
            to.parent = from.vertex;
            to.weight = weight;
            retval = true;
        }
        return retval;
    }

    bool relax(double weight, int from, int to, sssp::ShortestPaths& result)
    {
        return relax(weight, result[from], result[to]);
    }
} // namespace

bool sssp::bellman_ford(Graph const& graph, int source, sssp::ShortestPaths& output)
{
    auto result = initialize_single_source(graph, source);
    for (size_t i = 1, V = graph.size(); i < V; ++i) {
        for (int u = 0; u < static_cast<int>(V); ++u) {
            std::for_each(
                graph[u].begin(), graph[u].end(),
                [=, &result](auto v) { relax(v.second, u, v.first, result); }
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
                    return ((output[u].distance + v.second) < output[v.first].distance);
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
    void dfs(sssp::Graph const& graph, int vertex, std::vector<bool>& visited, std::vector<int>& leavers)
    {
        visited[vertex] = true;
        std::for_each(
            graph[vertex].cbegin(), graph[vertex].cend(),
            [=, &visited, &leavers](auto const &e) {
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
} // namespace

sssp::ShortestPaths sssp::dag(sssp::Graph const& graph, int source)
{
    auto leavers = toplogical_sort(graph);
    int i = 0, V = static_cast<int>(leavers.size());
    while (i < V && leavers[i] != source) {
        ++i;
    }
    auto result = initialize_single_source(graph, source);
    for (; i < V; ++i)
    {
        int v = leavers[i];
        std::for_each(
            graph[v].cbegin(), graph[v].cend(),
            [=, &result](const auto &e) {
                relax(e.second, v, e.first, result);
            }
        );
    }
    return result;
}

namespace
{
    template <typename T>
    struct KeyTrait;

    template <>
    struct KeyTrait<sssp::Edge>
    {
        using key_type = int;
        key_type key(const sssp::Edge& t) const { return t.vertex; }
        void swap(KeyTrait<sssp::Edge>&) {}
    };
}

sssp::ShortestPaths sssp::dijkstra(sssp::Graph const& graph, int source)
{
    auto comparator = [](const sssp::Edge& l, const sssp::Edge& r) {
        return l.distance > r.distance;
    };

    size_t V = graph.size();
    std::vector<bool> visited(V, false);
    heap::KaryHeap<16, sssp::Edge, decltype(comparator), KeyTrait> kary_heap(V);
    kary_heap.insert(sssp::Edge{-1, source, 0, 0});
    for (int i = 0, e = static_cast<int>(V); i != e; ++i) {
        if (i != source) {
            kary_heap.insert(sssp::Edge{i});
        }
    }

    std::vector<Edge> edges(V);
    while (!kary_heap.empty()) {
        auto ue = kary_heap.minimum();
        kary_heap.pop_min();
        edges[ue.vertex] = ue;
        visited[ue.vertex] = true;
        std::for_each(
            graph.adj(ue.vertex).begin(),
            graph.adj(ue.vertex).end(),
            [&ue, &visited, &kary_heap](auto vw) {
                auto [v, w] = vw;
                if (!visited[v]) {
                    decltype(auto) old_ve = kary_heap[sssp::Edge{v}];
                    auto ve(old_ve);
                    if (relax(w, ue, ve)) {
                        kary_heap.decrease(old_ve, ve);
                    }
                }
            }
        );
    }
    return sssp::ShortestPaths(std::move(edges));
}
