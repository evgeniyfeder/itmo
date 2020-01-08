import pyglet
from pyglet.gl import *
from math import radians, cos, sin

from draw.drawing_api import IDrawingApi
from draw.objects import Point, Circle


class PyGletDrawingApi(IDrawingApi):
    def __init__(self, w, h):
        self._w = w
        self._h = h

    def getDrawingAreaWidth(self) -> int:
        return self._w

    def getDrawingAreaHeight(self) -> int:
        return self._h

    def drawCircle(self, c: Circle):
        verts = []
        num_points = 1000
        for i in range(num_points):
            angle = radians(float(i) / num_points * 360.0)
            x = c.size * cos(angle) + c.p.x
            y = c.size * sin(angle) + c.p.y
            verts += [x, y]

        circle = pyglet.graphics.vertex_list(num_points, ('v2f', verts))
        circle.draw(GL_LINE_LOOP)

    def drawLine(self, p0: Point, p1: Point):
        glBegin(GL_LINES)
        glVertex3f(p0.x, p0.y, 0)
        glVertex3f(p1.x, p1.y, 0)
        glEnd()
