import abc
import attr
from draw.drawing_api import IDrawingApi


class AbstractGraph(metaclass=abc.ABCMeta):
    @abc.abstractmethod
    def __init__(self, drawing_api):
        self.drawing_api = drawing_api

    @staticmethod
    @abc.abstractmethod
    def read_graph(filename: str, draw_api: IDrawingApi):
        raise NotImplementedError

    @abc.abstractmethod
    def draw_graph(self):
        raise NotImplementedError
