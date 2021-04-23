#ifndef GRAPH_FACTORY_GYM_H
#define GRAPH_FACTORY_GYM_H

#include <sstream>
#include <fstream>
#include <filesystem>
#include <stdexcept>

template <typename Graph>
Graph create_graph(std::istream& is, bool getting_weight = true, bool is_undirected = true)
{
    char line[128] = { 0 }, * p = nullptr;
    is.getline(line, sizeof(line));
    size_t V = strtol(line, &p, 10);
    if (V > 0) {
        is.getline(line, sizeof(line));
        Graph g(V);
        while (!is.eof()) {
            is.getline(line, sizeof(line));
            int u = strtol(line, &p, 10);
            int v = strtol(p, &p, 10);
            float weight = 1.0;
            if (getting_weight) {
                weight = strtof(p, &p);
            }
            g.add_adge(u, v, weight);
            if (is_undirected) {
                g.add_adge(v, u, weight);
            }
        }
        return g;
    }
    else {
        throw std::runtime_error("File content is illegal");
    }
}

template <typename Graph>
Graph create_graph(const char* file_name, bool getting_weight = true, bool is_undirected = true)
{
    std::ifstream inf(file_name);
    if (inf.is_open()) {
        return create_graph<Graph>(inf, getting_weight, is_undirected);
    }
    else {
        throw std::runtime_error(std::string("Cannot open the file ") + file_name);
    }
}

#endif