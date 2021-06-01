'''
This module support the data structure: Graph and some common
functions related to the data structure
'''

import copy
from collections import deque


class Graph:
    '''Can use the class to represent a directed, undirected,
    or/and weighted graph'''

    class Edge:
        '''The class is used to represent the edge of a graph'''

        WEIGHT_LIMIT = 2 ** 128
        DEFAULT_WEIGHT = 1.0

        def __init__(self, weight=DEFAULT_WEIGHT, **kwargs):
            self.weight = weight
            for key, value in kwargs.items():
                setattr(self, str(key), value)

        def __eq__(self, e):
            equals = False
            if isinstance(e, Graph.Edge):
                equals = self.__dict__ == e.__dict__
            return equals

        def __ne__(self, e):
            return not self.__eq__(e)

        def _attrs_to_str(self):
            i = 0
            string = ""
            for key, value in self.__dict__.items():
                if i != 0:
                    string += ", "
                string += ("%s=%s" % (key, value))
                i += 1
            return string

        def __repr__(self):
            return "Graph.%s(%s)" % (
                self.__class__.__name__, self._attrs_to_str()
            )

    def __init__(self, V):
        self.count_of_vertices = V
        self.vertices = [{} for _i in range(V)]

    def __eq__(self, e):
        equals = False
        if isinstance(e, Graph):
            equals = (
                self.count_of_vertices == e.count_of_vertices and
                self.vertices == e.vertices
            )
        return equals

    def __ne__(self, e):
        return not self.__eq__(e)

    def __getitem__(self, start_vertex):
        assert 0 <= start_vertex < self.count_of_vertices
        return self.vertices[start_vertex]

    def __len__(self):
        return self.count_of_vertices

    def __repr__(self):
        retval = ""
        for i in range(self.count_of_vertices):
            if retval:
                retval += "\n"
            line = ""
            for vertex in self.vertices[i]:
                if line:
                    line += ", "
                line += "Graph.Edge(%d->%d, %s)" % (
                    i, vertex, self.vertices[i][vertex]
                )
            retval += ("%d:\t%s" % (i, line))
        return retval

    def add_edge(self,
                 start_vertex,
                 end_vertex,
                 weight=Edge.DEFAULT_WEIGHT,
                 **kwargs):
        '''add new edge to the graph'''

        self.vertices[start_vertex][end_vertex] = Graph.Edge(weight, **kwargs)
        return self

    def transpose(self):
        '''return a transposed graph'''

        graph = Graph(self.count_of_vertices)
        for i in range(self.count_of_vertices):
            for vertex in self.vertices[i]:
                graph.vertices[vertex][i] = copy.copy(self.vertices[i][vertex])
        return graph

    def __invert__(self):
        return self.transpose()


class Paths:
    '''The class is used to represent paths from a vertex to other vertices'''

    def __init__(self, path_dict):
        self.path_dict = path_dict

    def has_path_to(self, vertex):
        '''return a bool value to indicate whether there is a path from start_vertex
        vertex to the specified vertex'''
        return self.path_dict.get(vertex, None) is not None

    def path_to(self, vertex):
        path = []
        r = self.path_dict.get(vertex, None)
        if r is not None:
            path.append(vertex)
            parent = r.parent_vertex
            while parent != vertex:
                path.insert(0, parent)
                vertex = parent
                parent = self.path_dict.get(vertex).parent_vertex
        return tuple(path)


class BfsPaths(Paths):
    '''The class is used to represent BFS paths from a vertex
    to other vertices'''

    def distance(self, vertex):
        r = self.path_dict.get(vertex, None)
        if r is not None:
            r = r.distance
        return r


class Bfs:
    '''Its instances are function object, we can use them to do
    breadth-first search, and the return value is an instance of BfsPaths'''

    def __init__(self, graph, *vertices):
        self.graph = graph
        self.roots = vertices
        if not self.roots:
            raise ValueError(
                "you should have specified at least a starting vertex"
            )

    def __call__(self):
        class BfsPath:
            def __init__(self, vertex, distance, parent_vertex):
                self.vertex = vertex
                self.distance = distance
                self.parent_vertex = parent_vertex

        path_dict = {}
        count_of_vertices = len(self.graph)
        marked = [False for _i in range(count_of_vertices)]
        queue = deque()
        for v in self.roots:
            marked[v] = True
            queue.append(BfsPath(v, 0, v))
        while queue:
            bp = queue.popleft()
            path_dict[bp.vertex] = bp
            for e in self.graph[bp.vertex]:
                if not marked[e]:
                    marked[e] = True
                    queue.append(BfsPath(e, bp.distance + 1, bp.vertex))
        return BfsPaths(path_dict)


class Dfs:
    '''Its instances are function object, we can use them to do depth-first
    search, and the return value is an instance of Paths'''

    class Record:
        def __init__(self):
            self.entry_time = 0
            self.leaving_time = 0
            self.parent_vertex = -1
            self.visited = False

    def __init__(
        self,
        graph,
        *vertices,
        entry_action=None,
        leaving_action=None,
        restart_action=None
    ):
        self.count_of_vertices = len(graph)
        self.graph = graph
        self.roots = vertices
        self.dfs_tree_dict = {}
        n = len(self.roots)
        if n == 0 or (n == 1 and self.roots[0] < 0):
            self.roots = [_i for _i in range(self.count_of_vertices)]

        def do_nothing(vertex, parent_vertex, time): ...

        self.entry_action = entry_action
        if entry_action is None:
            self.entry_action = do_nothing
        self.leaving_action = leaving_action
        if leaving_action is None:
            self.leaving_action = do_nothing

        def do_nothing_2(dfs_tree_dict): ...

        self.restart_action = restart_action
        if restart_action is None:
            self.restart_action = do_nothing_2

    def _dfs(self, s):
        assert not self.records[s].visited
        self.records[s].visited = True
        self.clock += 1
        self.records[s].entry_time = self.clock
        self.entry_action(s, self.records[s].parent_vertex, self.clock)
        for v in self.graph[s]:
            if not self.records[v].visited:
                self.records[v].parent_vertex = s
                self._dfs(v)
        self.clock += 1
        self.records[s].leaving_time = self.clock
        self.leaving_action(s, self.records[s].parent_vertex, self.clock)
        self.dfs_tree_dict[s] = self.records[s]

    def __call__(self):
        class DfsPath:
            def __init__(self, parent_vertex):
                self.parent_vertex = parent_vertex

        self.records = [Dfs.Record() for _i in range(self.count_of_vertices)]
        self.clock = 0
        for v in self.roots:
            if (
                v >= 0 and
                v < self.count_of_vertices and
                not self.records[v].visited
            ):
                self.dfs_tree_dict.clear()
                self.records[v].parent_vertex = v
                self._dfs(v)
                self.dfs_tree_dict[v] = self.records[v]
                self.restart_action(self.dfs_tree_dict)

        path_dict = {}
        for i in range(self.count_of_vertices):
            if self.records[i].visited:
                path_dict[i] = DfsPath(self.records[i].parent_vertex)
        paths = Paths(path_dict)
        paths.records = self.records
        return paths


def topological_sort(graph):
    '''We should call the function with a directed graph'''
    sorted_vertices = []

    def sort_vertices(vertex, parent_vertex, time):
        sorted_vertices.insert(0, vertex)

    Dfs(graph, leaving_action=sort_vertices)()
    return tuple(sorted_vertices)


def get_strongly_connected_components(graph):
    '''We should call the function with a directed graph'''
    sorted_vertices = []

    def sort_vertices(vertex, parent_vertex, time):
        sorted_vertices.insert(0, vertex)

    Dfs(graph, leaving_action=sort_vertices)()

    strongly_connected_components = []

    def gather_vertices(dfs_tree_dict):
        strongly_connected_components.append(frozenset(dfs_tree_dict.keys()))

    Dfs(~graph, *sorted_vertices, restart_action=gather_vertices)()
    return strongly_connected_components


def create_undirected_graph(file_name):
    g = None
    with open(file_name, "r") as f:
        n = int(f.readline().strip())
        g = Graph(n)
        f.readline()  # ignore this line
        for line in f:
            (s, e, *other) = line.strip().split()
            w = 1.0
            if other:
                w = float(other[0])
            s = int(s)
            e = int(e)
            g.add_edge(s, e, w).add_edge(e, s, w)
    return g


def create_directed_graph(file_name):
    g = None
    with open(file_name, "r") as f:
        n = int(f.readline().strip())
        g = Graph(n)
        n = int(f.readline().strip())
        for i in range(n):
            (s, e, *other) = f.readline().strip().split()
            w = 1.0
            if other:
                w = float(other[0])
            s = int(s)
            e = int(e)
            g.add_edge(s, e, w)
    return g
