import pygame
from typing import Callable

from draw.pyglet_api import PyGletDrawingApi, IDrawingApi
from graph.abstract_graph import AbstractGraph
from draw.pygame_api import PyGameDrawingApi


def run_pygame(graph_factory: Callable[[str, IDrawingApi], AbstractGraph],
               graph_file: str,
               w: int, h: int):
    pygame.init()
    screen = pygame.display.set_mode((w, h))
    pygame.display.update()

    api = PyGameDrawingApi(w=w, h=h, drawing_surface=screen)
    graph = graph_factory(graph_file, api)

    running = True
    while running:
        ev = pygame.event.get()

        for event in ev:
            if event.type == pygame.QUIT:
                running = False

        graph.draw_graph()
        pygame.display.flip()
