package com.example;

import java.util.*;
import java.util.stream.Collectors;

/*
Book: <<Algorithms Fourth Edition>>
Chapter: 5.4 Regular Expressions
*/
public class NFA {
    private char[] regexp;
    private int numberOfStates;
    private Graph graph;

    public NFA(String inputRegexp) {
        this.regexp = inputRegexp.toCharArray();
        numberOfStates = this.regexp.length;
        graph = new Graph(numberOfStates + 1);

        Stack<Integer> ops = new Stack<>();
        for (int i = 0, last = numberOfStates - 1; i < numberOfStates;) {
            int nextI = i + 1;
            int lp = i;
            char re = regexp[i];
            if (re == '(' || re == '|') {
                ops.push(i);
            } else if (re == ')') {
                int op = ops.pop();
                if (regexp[op] == '|') {
                    lp = ops.pop();
                    graph.addAdge(lp, op + 1);
                    graph.addAdge(op, i);
                } else {
                    lp = op;
                }
            }

            if (i < last && regexp[nextI] == '*') {
                graph.addAdge(lp, nextI);
                graph.addAdge(nextI, lp);
            }

            if (re == '(' || re == '*' || re == ')') {
                graph.addAdge(i, nextI);
            }
            i = nextI;
        }
    }

    private static Collection<Integer> getReachableVertices(DfsVisitor.Result result) {
        Collection<Integer> reachableVertices = new ArrayList<>();
        for (int i = 0, M = result.size(); i < M; ++i) {
            if (result.isReachable(i)) {
                reachableVertices.add(i);
            }
        }
        return reachableVertices;
    }

    public boolean recognizes(String txt) {
        boolean retval = txt != null;
        if (retval) {
            DfsVisitor.Result result = new DfsVisitor(graph, 0).go();
            Collection<Integer> reachableVertices = getReachableVertices(result);

            char[] input = txt.toCharArray();
            for (int i = 0; i < input.length; ++i) {
                final char inputChar = input[i];
                Collection<Integer> match = reachableVertices.stream().filter(vertex -> {
                    int v = vertex.intValue();
                    return ((v < numberOfStates) && (regexp[v] == inputChar || regexp[v] == '.'));
                }).map(vertex -> {
                    return Integer.valueOf(vertex.intValue() + 1);
                }).collect(Collectors.toCollection(ArrayList<Integer>::new));

                result = new DfsVisitor(graph, match).go();
                reachableVertices = getReachableVertices(result);
            }
            retval = reachableVertices.stream().anyMatch(v -> v.intValue() == numberOfStates);
        }
        return retval;
    }
}