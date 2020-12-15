#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <filesystem>
#include <chrono>
#include "mst.h"
#include "check.h"

namespace
{
    const char* content =
        "9\n"
        "14\n"
        "0 1 4\n"
        "0 8 8\n"
        "1 2 8\n"
        "1 8 11\n"
        "2 3 7\n"
        "2 5 4\n"
        "2 7 2\n"
        "3 4 9\n"
        "3 5 14\n"
        "4 5 10\n"
        "5 6 2\n"
        "6 7 6\n"
        "6 8 1\n"
        "7 8 7\n";
    Graph crate_tesing_graph()
    {
        std::istringstream is(content);
        return mst::create_edge_weighted_graph(is);
    }

    bool equals(float f1, float f2)
    {
        if (abs((f1 - f2) / f1) < 0.00005) {
            return true;
        }
        return false;
    }
}

int main(int argc, char * argv[])
{
    if (argc == 1 || strcmp(argv[1], "test") == 0) {
        auto graph = crate_tesing_graph();
        auto result = mst::prim(graph);
        examine(result.weight == 37.0, "prim is wrong\n");
        auto result2 = mst::kruskal(graph);
        examine(result2.weight == 37.0, "kruskal is wrong\n");
        return 0;
    }
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            std::filesystem::path file(argv[i]);
            if (std::filesystem::is_regular_file(file)) {
                auto graph = mst::create_edge_weighted_graph(argv[i]);
                auto begin = std::chrono::system_clock::now();
                auto r1 = mst::prim(graph);
                auto end = std::chrono::system_clock::now();
                double prim_duration = std::chrono::duration<double>(end - begin).count();
                printf("prim: %f in %f seconds\n", r1.weight, prim_duration);
                auto printer = [](auto const& edges, bool showing_path_weight = true) {
                    for (const auto& e : edges) {
                        int u = e.parent, v = e.vertex;
                        if (u > v) {
                            std::swap(u, v);
                        }
                        printf("%d-%d %f",u, v, e.weight);
                        if (showing_path_weight) {
                            printf(", path_weight: %f", e.path_weight);
                        }
                        printf("\n");
                    }
                };

                begin = std::chrono::system_clock::now();
                auto r2 = mst::kruskal(graph);
                end = std::chrono::system_clock::now();
                double kruskal_duration = std::chrono::duration<double>(end - begin).count();
                printf("kruskal: %f in %f seconds\n", r2.weight, kruskal_duration);
                if (!equals(r1.weight, r2.weight)) {
                    printer(r2.edges, false);
                }
                examine(equals(r1.weight, r2.weight), "the return value %f of kruskal is different from that of prim (%f)\n", r2.weight, r1.weight);
            }
        }
    }
    return 0;
}
