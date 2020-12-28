import { Graph, DfsVisitor } from "./graph";


/*
Given an m x n 2d grid map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
*/

export function numIslands(grid: string[][]): number {
    function getVertex(n: number, i: number, j: number): number {
        return i * n + j;
    }

    let retval = 0;
    let m = grid.length;
    if (m > 0) {
        let n = grid[0].length;
        if (n > 0) {
            let V = m * n;
            let graph = new Graph(V);
            for (let i = 0, j = 0; i < m;) {
                if (grid[i][j] == '1') {
                    let v = getVertex(n, i, j);
                    if ((j-1) >= 0 && grid[i][j-1] == '1') {
                        graph.addEdge(v, v-1);
                    }
                    if ((j+1) < n && grid[i][j+1] == '1') {
                        graph.addEdge(v, v+1);
                    }
                    if ((i-1) >= 0 && grid[i-1][j] == '1') {
                        graph.addEdge(v, v-n);
                    }
                    if ((i+1) < m && grid[i+1][j] == '1') {
                        graph.addEdge(v, v+n);
                    }
                }
                ++j;
                if (j == n) {
                    j = 0;
                    ++i;
                }
            }
            let startVertices = [];
            for (let i = 0, j = 0; i < m;) {
                if (grid[i][j] === '1') {
                    let v = getVertex(n, i, j);
                    startVertices.push(v);
                }
                ++j;
                if (j == n) {
                    j = 0;
                    ++i;
                }
            }

            let dfsRecorder = {
                begin(vertex: number): void {},
                end(): void { ++retval; }
            };
            let visitor = new DfsVisitor(graph);
            visitor.setDfsRecorder(dfsRecorder);
            visitor.visit(...startVertices);
        }
    }
    return retval;
};
