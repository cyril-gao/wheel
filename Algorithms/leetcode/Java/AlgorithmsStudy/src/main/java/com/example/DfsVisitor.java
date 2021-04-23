package com.example;

import java.util.*;
import java.util.stream.*;

public class DfsVisitor {
    private static class Counter {
        private long counter = 0;

        public long getCount() {
            return counter++;
        }
    }

    public static class Result {
        public static final long NO_PARENT = -1;

        public enum Color {
            WHITE, GRAY, BLACK
        }

        public static class Item {
            public Color color = Color.WHITE;
            public long parent = Result.NO_PARENT;
            public long enter = 0;
            public long leave = 0;
        }

        private List<Item> record;

        public Result(int V) {
            assert (V > 0);
            record = Stream.generate(Item::new).limit(V).collect(Collectors.toList());
        }

        public boolean isReachable(int v) {
            return record.get(v).color != Color.WHITE;
        }

        public int size() {
            return record.size();
        }
    }

    Graph graph;
    Collection<Integer> startVertices;

    public DfsVisitor(Graph graph, Integer... vertices) {
        this.graph = graph;
        startVertices = Arrays.asList(vertices);
    }

    public DfsVisitor(Graph graph, Collection<Integer> vertices) {
        this.graph = graph;
        startVertices = vertices;
    }

    private void dfs(int u, DfsVisitor.Result result, Counter c) {
        assert (result.record.get(u).color == Result.Color.WHITE);
        result.record.get(u).color = Result.Color.GRAY;
        result.record.get(u).enter = c.getCount();
        for (int v : graph.adj(u)) {
            if (result.record.get(v).color == Result.Color.WHITE) {
                result.record.get(v).parent = u;
                dfs(v, result, c);
            }
        }
        result.record.get(u).leave = c.getCount();
        result.record.get(u).color = Result.Color.BLACK;
    }

    public Result go() {
        DfsVisitor.Result result = new DfsVisitor.Result(graph.size());
        Counter c = new Counter();
        for (int v : startVertices) {
            if (result.record.get(v).color == Result.Color.WHITE) {
                dfs(v, result, c);
            }
        }
        return result;
    }
}