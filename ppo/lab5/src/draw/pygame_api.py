import pygame

from draw.drawing_api import IDrawingApi
from draw.objects import Point, Circle


class PyGameDrawingApi(IDrawingApi):
    def __init__(self, w, h, drawing_surface: pygame.Surface):
        self._w = w
        self._h = h
        self._surface = drawing_surface

    def getDrawingAreaWidth(self) -> int:
        return self._w

    def getDrawingAreaHeight(self) -> int:
        return self._h

    def drawCircle(self, c: Circle):
        pygame.draw.circle(self._surface,
                           (255,0,0),
                           (c.p.x, c.p.y),
                           c.size)

    def drawLine(self, p0: Point, p1: Point):
        pygame.draw.line(self._surface,
                         (0,255,0),
                         (p0.x, p0.y),
                         (p1.x, p1.y))
