export class Graph
{
    private adjacency_list: Array<Array<number>>;
    
    constructor(public readonly V: number) {
        this.adjacency_list = new Array<Array<number>>(V);
        for (let i = 0; i < V; ++i) {
            this.adjacency_list[i] = [];
        }
    }

    public addEdge(from: number, to: number): Graph {
        this.adjacency_list[from].push(to);
        return this;
    }

    public adj(vertex: number): Array<number> {
        return this.adjacency_list[vertex];
    }
}

export enum Color {WHITE, GRAY, BLACK};

export class VertexState
{
    public parent: number;
    public color: Color;
    public distance: number;
    public enter: number;
    public leave: number;

    constructor() {
        this.clear();
    }

    public clear() {
        this.parent = -1;
        this.color = Color.WHITE;
        this.distance = 0;
        this.enter = 0;
        this.leave = 0;
    }
}

export interface Consumer {
    accept(vertex: number, state: VertexState): void;
}

export interface AdjacencyFilter {
    filter(vertex: number, state: VertexState, graph: Graph): Array<number>;
}

export interface DfsRecorder {
    begin(vertex: number): void;
    end(): void;
}

export class VertexStates
{
    constructor(private readonly states: Array<VertexState>) {}

    public hasPathTo(vertex: number): boolean {
        return this.states[vertex].color === Color.BLACK;
    }

    public getPathTo(vertex: number): Array<number> {
        let retval: Array<number> = [vertex];
        if (this.states[vertex].color === Color.BLACK) {
            let p = this.states[vertex].parent;
            while (p >= 0) {
                retval.unshift(p);
                p = this.states[p].parent;
            }
        }
        return retval;
    }
}

export class DfsVisitor
{
    private tick: number;
    private inConsumer: Consumer;
    private outConsumer: Consumer;
    private traversalConsumer: Consumer;
    private adjacencyFilter: AdjacencyFilter;
    private dfsRecorder: DfsRecorder;

    constructor(private readonly graph: Graph) {
        let doNothingConsumer: Consumer = {
            accept: function(vertex: number, state: VertexState) {}
        };

        let normalAdjacencyFilter: AdjacencyFilter = {
            filter: function(vertex: number, state: VertexState, graph: Graph): Array<number> {
                return graph.adj(vertex);
            }
        };

        let doNothingRecorder: DfsRecorder = {
            begin(vertex: number): void {},
            end(): void {}
        }

        this.inConsumer = doNothingConsumer;
        this.outConsumer = doNothingConsumer;
        this.traversalConsumer = doNothingConsumer;
        this.adjacencyFilter = normalAdjacencyFilter;
        this.dfsRecorder = doNothingRecorder;
    }

    public setInConsumer(inConsumer: Consumer): void {
        this.inConsumer = inConsumer;
    }

    public setOutConsumer(outConsumer: Consumer): void {
        this.outConsumer = outConsumer;
    }

    public setTraversalConsumer(traversalConsumer: Consumer): void {
        this.traversalConsumer = traversalConsumer;
    }

    public setAdjacencyFilter(adjacencyFilter: AdjacencyFilter): void {
        this.adjacencyFilter = adjacencyFilter;
    }

    public setDfsRecorder(dfsRecorder: DfsRecorder): void {
        this.dfsRecorder = dfsRecorder;
    }

    private dfs(vertex: number, states: Array<VertexState>): void {
        ++this.tick;
        states[vertex].color = Color.GRAY;
        states[vertex].enter = this.tick;
        this.inConsumer.accept(vertex, states[vertex]);
        let neighbours = this.adjacencyFilter.filter(vertex, states[vertex], this.graph);
        for (let neighbour of neighbours) {
            this.traversalConsumer.accept(neighbour, states[neighbour]);
            if (states[neighbour].color === Color.WHITE) {
                states[neighbour].parent = vertex;
                states[neighbour].distance = states[vertex].distance + 1;
                this.dfs(neighbour, states);
            }
        }
        ++this.tick;
        states[vertex].color = Color.BLACK;
        states[vertex].leave = this.tick;
        this.outConsumer.accept(vertex, states[vertex]);
    }

    public visit(...vertices: number[]): VertexStates {
        this.tick = -1;
        let states: Array<VertexState> = new Array<VertexState>(this.graph.V);
        for (let i = 0; i < this.graph.V; ++i) {
            states[i] = new VertexState();
        }
        for (let v of vertices) {
            if (v >= 0 && v < this.graph.V) {
                if (states[v].color === Color.WHITE) {
                    this.dfsRecorder.begin(v);
                    this.dfs(v, states);
                    this.dfsRecorder.end();
                }
            }
        }
        return new VertexStates(states);
    }  
}

export class BfsVisitor
{
    constructor(private readonly graph: Graph) {}

    public visit(...vertices: number[]): VertexStates {
        let states: Array<VertexState> = new Array<VertexState>(this.graph.V);
        for (let i = 0; i < this.graph.V; ++i) {
            states[i] = new VertexState();
        }
        let queue = [];
        for (let v of vertices) {
            states[v].color = Color.GRAY;
            queue.push(v);
        }
        while (queue.length > 0) {
            let u = queue.shift();
            let newDistance = states[u].distance + 1;
            for (let v of this.graph.adj(u)) {
                if (states[v].color === Color.WHITE) {
                    states[v].color = Color.GRAY;
                    states[v].distance = newDistance;
                    states[v].parent = u;
                    queue.push(v);
                }
            }
            states[u].color = Color.BLACK;
        }

        return new VertexStates(states);
    }
}
