class Graph
{
    private adjancentList: Map<string, number[]>[];
    constructor(public readonly V: number) {
        this.adjancentList = new Array<Map<string, number[]>>(V);
        for (let i = 0; i < V; ++i) {
            this.adjancentList[i] = new Map<string, number[]>();
        }
    }

    addAdge(from: number, to: number, by: string): void {
        let adj = this.adjancentList[from];
        if (adj.has(by)) {
            adj.get(by).push(to);
        } else {
            adj.set(by, [to]);
        }
    }

    adj(v: number): Map<string, number[]> {
        return this.adjancentList[v];
    }
}

function getFirstStates(graph: Graph): number[] {
    let retval = [0];
    let neighbours = graph.adj(0).get('');
    if (neighbours) {
        retval.push(...neighbours);
    }
    return retval;
}

function dfs(graph: Graph, vertex: number, visited: boolean[]): void {
    visited[vertex] = true;
    let neighbours = graph.adj(vertex).get('');
    if (neighbours) {
        for (let v of neighbours) {
            if (!visited[v]) {
                dfs(graph, v, visited);
            }
        }
    }
}

function getConnectedStates(graph: Graph, vertex: number): number[] {
    let visited = new Array<boolean>(graph.V);
    visited.fill(false);
    dfs(graph, vertex, visited);
    let retval = [];
    for (let i = 0; i < visited.length; ++i) {
        if (visited[i]) {
            retval.push(i);
        }
    }
    return retval;
}

function visit(c: string, graph: Graph, vertices: number[]): number[]
{
    let retval = new Set<number>();
    let visited = new Array<boolean>(graph.V);
    visited.fill(false);
    for (let v of vertices) {
        if (!visited[v]) {
            visited[v] = true;
            let adj = graph.adj(v);
            let neighbours = adj.get(c);
            if (neighbours) {
                neighbours.forEach(v => retval.add(v));
            }
            neighbours = adj.get('.');
            if (neighbours) {
                neighbours.forEach(v => retval.add(v));
            }
            retval.forEach(
                u => getConnectedStates(graph, u).forEach(w => retval.add(w))
            );
        }
    }
    return [...retval];
}

/*
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*' where: 
-  '.' Matches any single character.​​​​
-  '*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).
*/

export function isMatch(s: string, p: string): boolean {
    if (p.length > 0) {
        let graph = new Graph(p.length + 1);
        for (let i = 0; i < p.length;) {
            let c = p[i];
            let j = i + 1;
            if (c != '*') {
                graph.addAdge(i, j, c);
            } else {
                graph.addAdge(i, i - 1, '');
                let next = j;
                for (j = i; p[j] === '*';) {
                    --j;
                    graph.addAdge(j, next, '');
                    --j;
                }
                j = next;
            }
            i = j;
        }
        let state = getFirstStates(graph);
        for (let i = 0; i < s.length; ++i) {
            state = visit(s[i], graph, state);
        }
        return state.some(v => v === p.length);
    } else {
        return s.length == 0;
    }
}
