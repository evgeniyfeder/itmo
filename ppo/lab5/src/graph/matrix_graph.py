from graph.abstract_graph import AbstractGraph, IDrawingApi
from typing import List, Tuple
from draw.objects import get_node_pos, Circle, Point


class MatrixGraph(AbstractGraph):
    def __init__(self, num_nodes: int, matrix: List[List[int]], drawing_api: IDrawingApi):
        self._num_nodes = num_nodes
        self._matrix = matrix
        super().__init__(drawing_api)

    @staticmethod
    def read_graph(filename: str, draw_api: IDrawingApi):
        with open(filename, "rt") as inf:
            n, = (int(i) for i in inf.readline().split())

            matrix = []

            for i in range(n):
                matrix.append([int(i) for i in inf.readline().split()])
            return MatrixGraph(num_nodes=n, matrix=matrix, drawing_api=draw_api)

    def draw_graph(self):
        w = self.drawing_api.getDrawingAreaWidth()
        h = self.drawing_api.getDrawingAreaHeight()

        for i in range(self._num_nodes):
            p = get_node_pos(w, h, i, self._num_nodes)
            self.drawing_api.drawCircle(Circle(p=p, size=10))

        n = self._num_nodes
        for i in range(n):
            for j in range(i, n):
                if self._matrix[i][j]:
                    pi = get_node_pos(w, h, i, self._num_nodes)
                    pj = get_node_pos(w, h, j, self._num_nodes)

                    self.drawing_api.drawLine(pi, pj)
