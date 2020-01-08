import abc

from draw.objects import Point, Circle


class IDrawingApi(metaclass=abc.ABCMeta):
    @abc.abstractmethod
    def getDrawingAreaWidth(self) -> int:
        raise NotImplementedError

    @abc.abstractmethod
    def getDrawingAreaHeight(self) -> int:
        raise NotImplementedError

    @abc.abstractmethod
    def drawCircle(self, c: Circle):
        raise NotImplementedError

    @abc.abstractmethod
    def drawLine(self, p0: Point, p1: Point):
        raise NotImplementedError


