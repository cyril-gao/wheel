#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#define strcasecmp _stricmp
#else
#include <strings.h>
#endif

#include <filesystem>

#include "sssp.h"
#include "graph_factory.h"
#include "check.h"


namespace
{
    sssp::Graph create_graph_for_bellman_ford_method()
    {
        const char* content =
            "5\n"
            "10\n"
            "0 1 6\n"
            "0 3 7\n"
            "1 2 5\n"
            "1 3 8\n"
            "1 4 -4\n"
            "2 1 -2\n"
            "3 2 -3\n"
            "3 4 9\n"
            "4 0 2\n"
            "4 2 7\n";
        std::istringstream is(content);
        return create_graph<sssp::Graph>(is, true, false);
    }

    sssp::Graph create_graph_for_dag_method()
    {
        const char* content =
            "6\n"
            "10\n"
            "0 1 5\n"
            "0 2 3\n"
            "1 2 2\n"
            "1 3 6\n"
            "2 3 7\n"
            "2 4 4\n"
            "2 5 2\n"
            "3 4 -1\n"
            "3 5 1\n"
            "4 5 -2\n";
        std::istringstream is(content);
        return create_graph<sssp::Graph>(is, true, false);
    }

    sssp::Graph create_graph_for_dijkstra_method()
    {
        const char* content =
            "5\n"
            "10\n"
            "0 1 10\n"
            "0 3 5\n"
            "1 2 1\n"
            "1 3 2\n"
            "2 4 4\n"
            "3 1 3\n"
            "3 2 9\n"
            "3 4 2\n"
            "4 0 7\n"
            "4 2 6\n";
        std::istringstream is(content);
        return create_graph<sssp::Graph>(is, true, false);
    }

    sssp::Graph create_testing_graph(const char* file_name)
    {
        return create_graph<sssp::Graph>(file_name, true, false);
    }

    enum class MethodName { BELLMAN_FORD, DAG, DIJKSTRA };

    MethodName get_method_name(const char* str)
    {
        if (strcasecmp(str, "dag") == 0) {
            return MethodName::DAG;
        }
        else if (strcasecmp(str, "dijkstra") == 0) {
            return MethodName::DIJKSTRA;
        }
        return MethodName::BELLMAN_FORD;
    }
}

int main(int argc, char* argv[])
{
    if (argc == 1 || strcmp(argv[1], "test") == 0) {
        {
            auto graph = create_graph_for_bellman_ford_method();
            {
                sssp::ShortestPaths sp;
                auto result = sssp::bellman_ford(graph, 0, sp);
                examine(result && sp.get_distance(4) == -2.0, "bellman_ford is wrong\n");
            }
            {
                sssp::ShortestPaths sp;
                auto result = sssp::bellman_ford(graph, 3, sp);
                examine(result && sp.get_distance(1) == -5.0, "bellman_ford is wrong\n");
            }
        }
        {
            auto graph = create_graph_for_dag_method();
            {
                auto result = sssp::dag(graph, 1);
                examine(result.get_distance(5) == 3.0, "dag is wrong\n");
            }
            {
                auto result = sssp::dag(graph, 0);
                examine(result.get_distance(5) == 5.0, "dag is wrong\n");
            }
        }
        {
            auto graph = create_graph_for_dijkstra_method();
            {
                auto result = sssp::dijkstra(graph, 0);
                examine(
                    result[0].distance == 0.0 &&
                    result[1].distance == 8.0 &&
                    result[2].distance == 9.0 &&
                    result[3].distance == 5.0 &&
                    result[4].distance == 7.0,
                    "dijkstra is wrong\n"
                );
            }
        }
        return 0;
    }
    if (argc > 2) {
        auto method_name = get_method_name(argv[1]);
        for (int i = 2; i < argc; ++i) {
            std::filesystem::path file(argv[i]);
            if (std::filesystem::is_regular_file(file)) {
                sssp::ShortestPaths sp;
                bool successful = true;
                auto graph = create_testing_graph(argv[i]);
                if (method_name == MethodName::DAG) {
                    sp = std::move(sssp::dag(graph, 0));
                }
                else if (method_name == MethodName::DIJKSTRA) {
                    sp = std::move(sssp::dijkstra(graph, 0));
                }
                else {
                    successful = sssp::bellman_ford(graph, 0, sp);
                }
                if (successful) {
                    for (const auto& e : sp.edges) {
                        if (e.parent >= 0) {
                            printf("0->%-5d (parent: %-5d, weight: %f), distance: %f\n", e.vertex, e.parent, e.weight, e.distance);
                        }
                    }
                }
                else {
                    printf("The algorithm was failed for the file: %s\n", argv[i]);
                }
            }
        }
    }
    return 0;
}