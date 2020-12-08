import { Graph, Color, VertexState, Consumer, DfsVisitor } from "./graph";

export function canFinish(numCourses: number, prerequisites: number[][]): boolean {
    let graph = new Graph(numCourses);
    for (let pair of prerequisites) {
        graph.addEdge(pair[1], pair[0]);
    }
    let traversalConsumer: Consumer = {
        accept: function(vertex: number, state: VertexState) {
            if (state.color === Color.GRAY) {
                throw new Error("There is a cycle");
            }
        }
    };
    let visitor = new DfsVisitor(graph);
    visitor.setTraversalConsumer(traversalConsumer);
    try {
        visitor.visit(...Array(numCourses).keys());
        return true;
    } catch (e) {
        return false;
    }
};
