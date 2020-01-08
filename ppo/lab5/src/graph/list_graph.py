from graph.abstract_graph import AbstractGraph, IDrawingApi
from typing import List, Tuple
from draw.objects import get_node_pos, Circle, Point


class ListGraph(AbstractGraph):
    def __init__(self, num_nodes: int, edges: List[Tuple[int, int]], drawing_api: IDrawingApi):
        self._num_nodes = num_nodes
        self._edges = edges
        super().__init__(drawing_api)

    @staticmethod
    def read_graph(filename: str, draw_api: IDrawingApi):
        with open(filename, "rt") as inf:
            n, m = (int(i) for i in inf.readline().split())

            edgs = []
            for i in range(m):
                from_i, to_i = (int(i) for i in inf.readline().split())
                edgs.append((from_i, to_i))
            return ListGraph(num_nodes=n, edges=edgs, drawing_api=draw_api)

    def draw_graph(self):
        w = self.drawing_api.getDrawingAreaWidth()
        h = self.drawing_api.getDrawingAreaHeight()

        for i in range(self._num_nodes):
            p = get_node_pos(w, h, i, self._num_nodes)
            self.drawing_api.drawCircle(Circle(p=p, size=10))

        for i, j in self._edges:
            pi = get_node_pos(w, h, i, self._num_nodes)
            pj = get_node_pos(w, h, j, self._num_nodes)

            self.drawing_api.drawLine(pi, pj)
