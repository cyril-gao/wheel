#ifndef GRAPY_GYM_H
#define GRAPY_GYM_H

#include <assert.h>

#include <algorithm>
#include <forward_list>
#include <stack>
#include <vector>

class DfsVisitor;

class Graph
{
public:
    struct Edge
    {
        int vertex;
        float weight{1.0};
    };
private:
    std::vector<std::forward_list<Edge>> m_adjacency_list;
    std::vector<std::forward_list<Edge>::iterator> m_last_positions;

    friend class DfsVisitor;
public:
    explicit Graph(size_t V) : m_adjacency_list(V)
    {
        m_last_positions.reserve(V);
        for (auto & al : m_adjacency_list) {
            m_last_positions.push_back(al.before_begin());
        }
    }
    void add_adge(int from, int to, float weight = 1.0)
    {
        assert(from >= 0 && to >= 0);
        assert(static_cast<size_t>(from) < m_adjacency_list.size());
        assert(static_cast<size_t>(to) < m_adjacency_list.size());
        m_last_positions[from] = m_adjacency_list[from].insert_after(m_last_positions[from], Edge{to, weight});
    }
    const std::forward_list<Edge> & adj(size_t i) const
    {
        return m_adjacency_list[i];
    }
    const std::forward_list<Edge>& operator[](size_t i) const
    {
        return m_adjacency_list[i];
    }
    size_t size() const { return m_adjacency_list.size(); }
};

class DfsResult
{
    friend class DfsVisitor;
    enum {NO_PARENT = -1};
    enum class Color {WHITE, GRAY, BLACK};
    struct Trace
    {
        int parent{NO_PARENT};
        Color color{Color::WHITE};
        int enter{-1};
        int leave{-1};
    };
    std::vector<Trace> m_record;
public:
    std::vector<int> get_path_to(int vertex) const
    {
        std::vector<int> retval;
        if (m_record[vertex].color != Color::WHITE) {
            std::stack<int> ancestors;
            for (int i = m_record[vertex].parent; i != NO_PARENT; i = m_record[i].parent) {
                ancestors.push(i);
            }
            if (!ancestors.empty()) {
                retval.reserve(ancestors.size());
                while (!ancestors.empty()) {
                    retval.push_back(ancestors.top());
                    ancestors.pop();
                }
            }
        }
        return retval;
    }
    bool is_reachable(int vertex) const
    {
        return m_record[vertex].color != Color::WHITE;
    }
};

class DfsVisitor
{
    const Graph & m_graph;
    std::vector<int> m_start_vertices;

    void dfs(int vertex, DfsResult & result, int & counter) const
    {
        assert(result.m_record[vertex].color == DfsResult::Color::WHITE);
        result.m_record[vertex].color = DfsResult::Color::GRAY;
        result.m_record[vertex].enter = counter++;
        std::for_each(
            m_graph.m_adjacency_list[vertex].cbegin(),
            m_graph.m_adjacency_list[vertex].cend(),
            [&result, &counter, this, vertex](auto child) {
                if (result.m_record[child.vertex].color == DfsResult::Color::WHITE) {
                    result.m_record[child.vertex].parent = vertex;
                    dfs(child.vertex, result, counter);
                }
            }
        );
        result.m_record[vertex].leave = counter++;
        result.m_record[vertex].color = DfsResult::Color::BLACK;
    }
public:
#if (defined(_WIN32) || defined(_WIN64))
    template <typename... Args>
    DfsVisitor(const Graph& graph, Args... vertices) : m_graph(graph)
    {
        (m_start_vertices.push_back(vertices), ...);
    }
#else
    DfsVisitor(const Graph & graph, auto... vertices) : m_graph(graph)
    {
        (m_start_vertices.push_back(vertices), ...);
    }
#endif
    DfsVisitor(const Graph & graph, std::vector<int> && vertices) :
        m_graph(graph), m_start_vertices(std::move(vertices))
    {
    }
    DfsVisitor(const Graph & graph, const std::vector<int> & vertices) :
        DfsVisitor(graph, std::vector<int>(vertices))
    {
    }
    DfsResult operator()() const
    {
        DfsResult result;
        result.m_record.resize(m_graph.size());
        int counter = 0;
        for (auto v : m_start_vertices) {
            if (result.m_record[v].color == DfsResult::Color::WHITE) {
                dfs(v, result, counter);
            }
        }
        return result;
    }
};

#endif
