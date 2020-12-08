export class Graph
{
    private adjacency_list: Array<Array<number>>;
    
    constructor(public readonly V: number) {
        this.adjacency_list = new Array<Array<number>>(V);
        for (let i = 0; i < V; ++i) {
            this.adjacency_list[i] = [];
        }
    }

    public addEdge(from: number, to: number): void {
        this.adjacency_list[from].push(to);
    }

    public adj(vertex: number): Array<number> {
        return this.adjacency_list[vertex];
    }
}

export enum Color {WHITE, GRAY, BLACK};

export class VertexState
{
    public parent: number = -1;
    public color: Color = Color.WHITE;
    public enter: number = 0;
    public leave: number = 0;
}

export interface Consumer {
    accept(vertex: number, state: VertexState): void;
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
    private inConsumer?: Consumer;
    private outConsumer?: Consumer;
    private traversalConsumer?: Consumer;

    constructor(
        private readonly graph: Graph,
        inConsumer?: Consumer,
        outConsumer?: Consumer,
        traversalConsumer?: Consumer
    ) {
        this.tick = 0;

        //let doNothing: Consumer = (vertex: number, state: VertexState): void => {};
        let doNothing: Consumer = {
            accept: function(vertex: number, state: VertexState) {}
        };

        if (inConsumer) {
            this.inConsumer = inConsumer;
        } else {
            this.inConsumer = doNothing;
        }

        if (outConsumer) {
            this.outConsumer = outConsumer;
        } else {
            this.outConsumer = doNothing;
        }

        if (traversalConsumer) {
            this.traversalConsumer = traversalConsumer;
        } else {
            this.traversalConsumer = doNothing;
        }
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

    private dfs(vertex: number, states: Array<VertexState>): void {
        ++this.tick;
        states[vertex].color = Color.GRAY;
        states[vertex].enter = this.tick;
        this.inConsumer.accept(vertex, states[vertex]);
        for (let neighbour of this.graph.adj(vertex)) {
            this.traversalConsumer.accept(neighbour, states[neighbour]);
            if (states[neighbour].color === Color.WHITE) {
                states[neighbour].parent = vertex;
                this.dfs(neighbour, states);
            }
        }
        ++this.tick;
        states[vertex].color = Color.BLACK;
        states[vertex].leave = this.tick;
        this.outConsumer.accept(vertex, states[vertex]);
    }

    public visit(...vertices: number[]): VertexStates {
        this.tick = 0;
        let states: Array<VertexState> = new Array<VertexState>(this.graph.V);
        for (let i = 0; i < this.graph.V; ++i) {
            states[i] = new VertexState();
        }
        for (let v of vertices) {
            if (v >= 0 && v < this.graph.V) {
                if (states[v].color === Color.WHITE) {
                    this.dfs(v, states);
                }
            }
        }
        return new VertexStates(states);
    }  
}
