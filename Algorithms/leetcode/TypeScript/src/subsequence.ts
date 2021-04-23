import { Graph, Color, Consumer, VertexState, DfsVisitor } from "./graph";


/*
Given two strings s and t, return the number of distinct subsequences of s which equals t.

A string's subsequence is a new string formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ACE" is a subsequence of "ABCDE" while "AEC" is not).

It's guaranteed the answer fits on a 32-bit signed integer.

 

Example 1:
Input: s = "rabbbit", t = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from S.
rabbbit
rabbbit
rabbbit


Example 2:
Input: s = "babgbag", t = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from S.
babgbag
babgbag
babgbag
babgbag
babgbag
*/

export function numDistinct(s: string, t: string): number {
    let retval = 0;
    if (s.length >= t.length) {
        let graph = new Graph(s.length);
        for (let i = 0, sn_1 = s.length - 1; i < sn_1; ++i) {
            for (let j = i + 1; j < s.length; ++j) {
                graph.addEdge(i, j);
            }
        }
        for (let si = 0;;) {
            if (s[si] == t[0]) {
                let indexInWord = -1;
                let inConsumer: Consumer = {
                    accept: function(vertex: number, state: VertexState) {
                        ++indexInWord;
                    }
                };
                let outConsumer: Consumer = {
                    accept: function(vertex: number, state: VertexState) {
                        state.color = Color.WHITE;
                        --indexInWord;
                    }
                };
                let adjacencyFilter = {
                    filter: function(vertex: number, graph: Graph): Array<number> {
                        let filterRetval = [];
                        let nextIndexInWord = indexInWord + 1;
                        if (nextIndexInWord < t.length) {
                            let c = t[nextIndexInWord];
                            for (let u of graph.adj(vertex)) {
                                if (s[u] == c) {
                                    filterRetval.push(u);
                                }
                            }
                        } else {
                            ++retval;
                        }
                        return filterRetval;
                    }
                };
                let visitor = new DfsVisitor(graph);
                visitor.setInConsumer(inConsumer);
                visitor.setOutConsumer(outConsumer);
                visitor.setAdjacencyFilter(adjacencyFilter);
                visitor.visit(si);
            }
            ++si;
            if ((s.length - si) < t.length) {
                break;
            }
        }
    }
    return retval;
}
