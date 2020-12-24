//prim.cpp
#include <algorithm>
#include <vector>
#include <unordered_map>
#include "mst.h"

#include <kary_heap.h>
#include <fibonacci_heap.h>


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

    template <typename Heap>
    mst::MST prim_impl(const Graph& graph)
    {
        auto V = graph.size();
        mst::MST retval(V);

        Heap heap;
        heap.insert(mst::Edge{ 0, 0 });
        for (int i = 1, e = static_cast<int>(V); i < e; ++i) {
            heap.insert(mst::Edge{ i });
        }
        std::vector<bool> visited(V, false);
        while (!heap.empty()) {
            auto u = heap.minimum();
            heap.pop_min();
            visited[u.vertex] = true;
            retval.weight += u.weight;
            u.path_weight = retval.weight;
            retval.edges[u.vertex] = u;

            std::for_each(
                graph.adj(u.vertex).begin(),
                graph.adj(u.vertex).end(),
                [uv = u.vertex, &visited, &heap](auto v) {
                    if (!visited[v.vertex]) {
                        mst::Edge ve{ v.vertex };
                        decltype(auto) old = heap[ve];
                        if (old.weight > v.weight) {
                            ve.parent = uv;
                            ve.weight = v.weight;
                            heap.decrease(old, ve);
                        }
                    }
                }
            );
        }
        return retval;
    }
}

mst::MST mst::prim(const Graph& graph)
{
    auto comparator = [](const mst::Edge& l, const mst::Edge& r) {
        return l.weight > r.weight;
    };
    /*
     * the performance is still not good:
     * return prim_impl<heap::FibonacciHeap<mst::Edge, decltype(comparator), KeyTrait>>(graph);
     */
     return prim_impl<heap::KaryHeap<16, mst::Edge, decltype(comparator), KeyTrait>>(graph);
}
