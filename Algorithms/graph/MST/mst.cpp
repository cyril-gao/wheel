#include <stdlib.h>
#include "mst.h"
#include "graph_factory.h"

Graph mst::create_edge_weighted_graph(std::istream& is)
{
    return create_graph<Graph>(is);
}

Graph mst::create_edge_weighted_graph(const char* file_name)
{
    return create_graph<Graph>(file_name);
}