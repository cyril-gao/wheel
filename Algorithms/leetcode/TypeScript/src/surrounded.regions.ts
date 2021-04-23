import { Graph, VertexState, DfsVisitor } from "./graph";

/*
Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example:

X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
Explanation:

Surrounded regions shouldn’t be on the border, which means that any 'O' on the border of the board are not flipped to 'X'. Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'. Two cells are connected if they are adjacent cells connected horizontally or vertically.
*/

export function solve(board: string[][]): void
{
    function getVertex(n: number, i: number, j: number): number {
        return i * n + j;
    }
    function getCoordinate(n: number, index: number): number[] {
        let i = Math.floor(index / n);
        let j = index % n;
        return [i, j];
    }

    let m = board.length;
    if (m > 1) {
        let n = board[0].length;
        if (n > 1) {
            let V = m * n;
            let graph = new Graph(V);
            for (let i = 0, j = 0; i < m;) {
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
            let startVertices = [];
            for (let i = 0, j = 0; i < m;) {
                if (board[i][j] === 'O') {
                    let v = getVertex(n, i, j);
                    startVertices.push(v);
                }
                ++j;
                if (j == n) {
                    j = 0;
                    ++i;
                }
            }

            let groups = new Map<number, Array<number>>();
            let startVertex = -1;

            let outConsumer = {
                accept(vertex: number, state: VertexState): void {
                    let group = groups.get(startVertex);
                    group.push(vertex);
                }
            };

            let dfsRecorder = {
                begin(vertex: number): void {
                    startVertex = vertex;
                    groups.set(vertex, [vertex]);
                },
                end(): void {
                    let group = groups.get(startVertex);
                    if (group.length > 0) {
                        let needToRefill = true;
                        for (let v of group) {
                            let coor = getCoordinate(n, v);
                            if (coor[0] === 0 || coor[0] === (m-1)) {
                                needToRefill = false;
                                break;
                            }
                            if (coor[1] === 0 || coor[1] === (n-1)) {
                                needToRefill = false;
                                break;
                            }
                        }
                        if (needToRefill) {
                            for (let v of group) {
                                let coor = getCoordinate(n, v);
                                board[coor[0]][coor[1]] = 'X';
                            }
                        }
                    }
                }
            };

            let adjacencyFilter = {
                filter: function(vertex: number, graph: Graph): Array<number> {
                    let filterRetval = [];
                    for (let u of graph.adj(vertex)) {
                        let coor = getCoordinate(n, u);
                        if (board[coor[0]][coor[1]] === 'O') {
                            filterRetval.push(u);
                        }
                    }
                    return filterRetval;
                }
            };

            let visitor = new DfsVisitor(graph);
            visitor.setOutConsumer(outConsumer);
            visitor.setAdjacencyFilter(adjacencyFilter);
            visitor.setDfsRecorder(dfsRecorder);
            visitor.visit(...startVertices);
        }
    }
};
