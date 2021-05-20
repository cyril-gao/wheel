import { Graph, VertexState, DfsVisitor } from "./graph";

/*
Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

Example 1:
Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]

Example 2:
Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []
*/

function getCoordinate(n: number, index: number): number[] {
    let i = Math.floor(index / n);
    let j = index % n;
    return [i, j];
}

export function findWords(board: string[][], words: string[]): string[] {
    function getVertex(n: number, i: number, j: number): number {
        return i * n + j;
    }

    let uniqueRetval = new Set<string>();
    let retval = [];
    let m = board.length;
    if (m > 0) {
        let n = board[0].length;
        if (n > 0) {
            let V = m * n;
            let graph = new Graph(V);
            for (let i = 0, j = 0; i < m && j < n;) {
                let v = getVertex(n, i, j);
                if ((j-1) >= 0) {
                    graph.addEdge(v, v-1);
                }
                if ((j+1) < n) {
                    graph.addEdge(v, v+1);
                }
                if ((i-1) >= 0) {
                    graph.addEdge(v, v-n);
                }
                if ((i+1) < m) {
                    graph.addEdge(v, v+n);
                }
                ++j;
                if (j == n) {
                    j = 0;
                    ++i;
                }
            }
            for (let word of words) {
                let i = 0, j = 0;
                while (i < m) {
                    while (i < m) {
                        if (board[i][j] == word[0]) {
                            break;
                        }
                        ++j;
                        if (j == n) {
                            j = 0;
                            ++i;
                        }
                    }
                    if (i < m) {
                        let map = new Map<number, number>();
                        let startVertex = getVertex(n, i, j);
                        let outConsumer = {
                            accept(vertex: number, state: VertexState): void {
                                state.clear();
                            }
                        };
                        let adjacencyFilter = {
                            filter: function(vertex: number, state: VertexState, graph: Graph): Array<number> {
                                let filterRetval = [];
                                let nextIndexInWord = state.distance + 1;
                                if (nextIndexInWord < word.length) {
                                    let c = word[nextIndexInWord];
                                    for (let u of graph.adj(vertex)) {
                                        let cor = getCoordinate(n, u);
                                        if (board[cor[0]][cor[1]] == c) {
                                            filterRetval.push(u);
                                            map.set(u, nextIndexInWord);
                                        }
                                    }
                                } else {
                                    if (!uniqueRetval.has(word)) {
                                        retval.push(word);
                                        uniqueRetval.add(word);
                                    }
                                }
                                return filterRetval;
                            }
                        };
                        let visitor = new DfsVisitor(graph);
                        visitor.setAdjacencyFilter(adjacencyFilter);
                        visitor.setOutConsumer(outConsumer);
                        visitor.visit(startVertex);
                        ++j;
                        if (j == n) {
                            j = 0;
                            ++i;
                        }
                    }
                }
            }
        }
    }
    return retval;
}


/*
Given an m x n grid of characters board and a string word, return true if word
exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where
adjacent cells are horizontally or vertically neighboring. The same letter cell
may not be used more than once.
*/

export function exist(board: string[][], word: string): boolean {
    let m = board.length;
    if (m > 0) {
        let n = board[0].length;
        if (n > 0) {
            let graph = new Graph(m * n);
            for (let i = 0; i < m; ++i) {
                for (let j = 0; j < n; ++j) {
                    let v = i * n + j;
                    if (j > 0) {
                        graph.addEdge(v, v - 1);
                    }
                    if ((j + 1) < n) {
                        graph.addEdge(v, v + 1);
                    }
                    if (i > 0) {
                        graph.addEdge(v, v - n);
                    }
                    if ((i + 1) < m) {
                        graph.addEdge(v, v + n);
                    }
                }
            }
            let retval = false;
            for (let i = 0; i < m && !retval; ++i) {
                for (let j = 0; j < n && !retval; ++j) {
                    if (board[i][j] === word[0]) {
                        let start = i * n + j;
                        let dfs = new DfsVisitor(graph);
                        let outConsumer = {
                            accept(vertex: number, state: VertexState): void {
                                state.clear();
                            }
                        };
                        let filter = {
                            filter: function(vertex: number, state: VertexState, graph: Graph): Array<number> {
                                let neighbours = [];
                                let result = graph.adj(vertex);
                                let nextIndex = state.distance + 1;
                                if (nextIndex < word.length) {
                                    for (let v of result) {
                                        let [row, col] = getCoordinate(n, v);
                                        if (board[row][col] === word[nextIndex]) {
                                            neighbours.push(v);
                                        }
                                    }
                                } else {
                                    retval = true;
                                }
                                return neighbours;
                            }
                        };
                        dfs.setAdjacencyFilter(filter);
                        dfs.setOutConsumer(outConsumer);
                        dfs.visit(start);
                    }
                }
            }
            return retval;
        }
    }
    return word.length === 0;
}
