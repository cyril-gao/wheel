import { Graph, BfsVisitor } from "./graph";

function equals<T>(elements1: T[], elements2: T[]): boolean {
    let retval = elements1.length === elements2.length;
    if (retval) {
        for (let i = 0; i < elements1.length; ++i) {
            if (elements1[i] !== elements2[i]) {
                retval = false;
                break;
            }
        }
    }
    return retval;
}

test(
    "check the result value of the call to the function BfsVisitor.visit",
    () => {
        let graph = new Graph(14);
        graph.addEdge(0, 4).addEdge(0, 5).addEdge(0, 11);
        graph.addEdge(1, 2).addEdge(1, 4).addEdge(1, 8);
        graph.addEdge(2, 5).addEdge(2, 6).addEdge(2, 9);
        graph.addEdge(3, 2).addEdge(3, 6).addEdge(3, 13);
        graph.addEdge(4, 7);
        graph.addEdge(5, 8).addEdge(5, 12);
        graph.addEdge(6, 5);
        graph.addEdge(8, 7);
        graph.addEdge(9, 10).addEdge(9, 11);
        graph.addEdge(10, 13);
        graph.addEdge(12, 9);

        let bfs = new BfsVisitor(graph);
        let result = bfs.visit(0);
        expect(result.hasPathTo(13)).toBe(true);
        expect(result.hasPathTo(3)).toBe(false);
        expect(equals(result.getPathTo(13), [0, 5, 12, 9, 10, 13])).toBe(true);
    }
);
