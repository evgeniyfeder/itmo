import pyglet

from draw.pyglet_api import PyGletDrawingApi, IDrawingApi
from graph.abstract_graph import AbstractGraph
from typing import Callable


def run_pyglet(graph_factory: Callable[[str, IDrawingApi], AbstractGraph],
               graph_file: str,
               w: int, h: int):
    window = pyglet.window.Window(width=w, height=h)

    api = PyGletDrawingApi(w=w, h=h)
    graph = graph_factory(graph_file, api)

    @window.event
    def on_draw():
        window.clear()

        graph.draw_graph()

    pyglet.app.run()
