import attr
import math


@attr.s(auto_attribs=True)
class Point:
    x: int
    y: int


@attr.s(auto_attribs=True)
class Circle:
    p: Point
    size: int


def get_node_pos(w: int, h: int, i: int, n: int):
    return Point(int(math.cos(2 * math.pi * (i / n)) * w / 4 + w / 2),
                 int(math.sin(2 * math.pi * (i / n)) * h / 4 + h / 2))
