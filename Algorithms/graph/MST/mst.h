#ifndef MST_GYM_H
#define MST_GYM_H

#include <limits.h>
#include <float.h>
#include <iosfwd>
#include "graph.h"

namespace mst
{
    struct Edge
    {
        int parent;
        int vertex;
        float weight;
        float path_weight;

        Edge(int p, int v, float w, float pw) :
            parent(p), vertex(v), weight(w), path_weight(pw)
        {
        }
        Edge(int vertex = -1, float weight = FLT_MAX) :
            Edge(-1, vertex, weight, FLT_MAX)
        {
        }
    };

    struct MST
    {
        std::vector<Edge> edges;
        float weight;

        MST(size_t V = 0) : edges(V), weight(0) {}
    };

    Graph create_edge_weighted_graph(std::istream& is);
    Graph create_edge_weighted_graph(const char* file_name);

    MST prim(const Graph& graph);

    MST kruskal(const Graph& graph);
}

#endif