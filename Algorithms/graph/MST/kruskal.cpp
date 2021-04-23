// kruskal
#include "mst.h"
#include "uf.h"

mst::MST mst::kruskal(const Graph& graph)
{
    std::vector<mst::Edge> edges;
    size_t V = graph.size();
    edges.reserve(V * 2);
    for (int i = 0; i < static_cast<int>(V); ++i) {
        for (auto e : graph[i]) {
            if (i < e.vertex) {
                edges.emplace_back(mst::Edge{ i, e.vertex, e.weight, FLT_MAX });
            }
        }
    }
    std::sort(
        edges.begin(), edges.end(),
        [](mst::Edge const& e1, mst::Edge const& e2) { return e1.weight < e2.weight; }
    );
    mst::MST retval;
    uf::ArrayBasedUF abuf(V);
    size_t count = 0;
    for (auto const& e : edges) {
        if (!abuf.connected(e.parent, e.vertex)) {
            abuf.connect(e.parent, e.vertex);
            retval.weight += e.weight;
            retval.edges.push_back(e);
            ++count;
            if ((count + 1) == V) {
                break;
            }
        }
    }
    assert(abuf.count() == 1);
    return retval;
}