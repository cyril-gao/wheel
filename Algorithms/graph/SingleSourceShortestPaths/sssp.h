#ifndef SINGLE_SOURCE_SHORTEST_PATHS_GYM_H
#define SINGLE_SOURCE_SHORTEST_PATHS_GYM_H

#include <assert.h>
#include <float.h>
#include <vector>
#include <unordered_map>

// Single Source Shortest paths
namespace sssp
{
    class Graph
    {
        mutable std::vector<std::unordered_map<int, double>> m_adjacency_list;

    public:
        explicit Graph(size_t V) : m_adjacency_list(V)
        {
        }
        void add_adge(int from, int to, double weight = 1.0)
        {
            assert(from >= 0 && to >= 0);
            assert(static_cast<size_t>(from) < m_adjacency_list.size());
            assert(static_cast<size_t>(to) < m_adjacency_list.size());
            m_adjacency_list[from][to] = weight;
        }
        const std::unordered_map<int, double>& adj(size_t i) const
        {
            return m_adjacency_list[i];
        }
        const std::unordered_map<int, double>& operator[](size_t i) const
        {
            return m_adjacency_list[i];
        }
        size_t size() const { return m_adjacency_list.size(); }
    };

    struct Edge
    {
        int parent;
        int vertex;
        float weight;
        float distance;

        Edge(int p, int v, float w, float d) :
            parent(p), vertex(v), weight(w), distance(d)
        {
        }
        Edge(int vertex = -1, float weight = FLT_MAX) :
            Edge(-1, vertex, weight, FLT_MAX)
        {
        }
    };

    struct ShortestPaths
    {
        std::vector<Edge> edges;

        ShortestPaths() = default;
        ShortestPaths(std::vector<Edge>&& es) : edges(std::move(es)) {}

        Edge& operator[](size_t vertex) { return edges[vertex]; }
        const Edge& operator[](size_t vertex) const { return edges[vertex]; }
        void swap(ShortestPaths& other)
        {
            edges.swap(other.edges);
        }

        std::vector<int> get_path(int vertex) const;
        float get_distance(int vertex) const;
    };

    bool bellman_ford(Graph const& graph, int source, ShortestPaths& output);
    ShortestPaths dag(Graph const& graph, int source);
    ShortestPaths dijkstra(Graph const& graph, int source);
} // namespace sssp

#endif