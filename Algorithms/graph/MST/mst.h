#ifndef MST_GYM_H
#define MST_GYM_H

#include <limits.h>
#include <float.h>
#include <iosfwd>
#include "graph.h"
#include "merge.h"

namespace mst
{
    struct Edge
    {
        int parent{-1};
        int vertex{-1};
        float weight{FLT_MAX};
        float path_weight{FLT_MAX};
    };

    struct MST
    {
        std::vector<Edge> edges;
        float weight{0};
    };

    Graph create_edge_weighted_graph(std::istream& is);
    Graph create_edge_weighted_graph(const char* file_name);

    MST prim(const Graph& graph);

    MST kruskal(const Graph& graph);
}

#endif