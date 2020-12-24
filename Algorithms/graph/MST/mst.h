#ifndef MST_GYM_H
#define MST_GYM_H

#include <limits.h>
#include <float.h>
#include <iosfwd>
#include "graph.h"

#if ( defined( _DEBUG ) || defined( DEBUG ) || defined( DBG ) )
#define MST_MAX_WEIGHT 100000.0
#else
#define MST_MAX_WEIGHT FLT_MAX
#endif


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
        Edge(int vertex = -1, float weight = MST_MAX_WEIGHT) :
            Edge(-1, vertex, weight, MST_MAX_WEIGHT)
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