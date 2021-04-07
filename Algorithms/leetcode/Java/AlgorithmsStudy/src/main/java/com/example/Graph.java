package com.example;

import java.util.*;
import java.util.stream.*;

public class Graph {
    private List<Collection<Integer>> adjacencyList;

    public Graph(int V) {
        assert (V > 0);
        adjacencyList = Stream.generate(LinkedList<Integer>::new).limit(V).collect(Collectors.toList());
    }

    void addAdge(int from, int to) {
        assert (from >= 0 && to >= 0);
        assert (from < adjacencyList.size());
        assert (to < adjacencyList.size());
        adjacencyList.get(from).add(Integer.valueOf(to));
    }

    Collection<Integer> adj(int v) {
        assert (v >= 0 && v < adjacencyList.size());
        return adjacencyList.get(v);
    }

    int size() {
        return adjacencyList.size();
    }
}

