import argparse

from apps.pyglet_app import run_pyglet
from apps.pygame_app import run_pygame

from graph.list_graph import ListGraph
from graph.matrix_graph import MatrixGraph

GRAPH_FACTORIES = {"list": ListGraph.read_graph, "matrix": MatrixGraph.read_graph}


def main():
    parser = argparse.ArgumentParser()

    parser.add_argument("draw_api", type=str, choices=["pyglet", "pygame"], default="pygame")
    parser.add_argument("graph", type=str, choices=GRAPH_FACTORIES.keys(), default="list")
    parser.add_argument("graph_filename", type=str)
    parser.add_argument("--width", default=800)
    parser.add_argument("--height", default=800)
    args = parser.parse_args()

    if args.draw_api == "pyglet":
        run_pyglet(GRAPH_FACTORIES[args.graph], args.graph_filename, args.width, args.height)
    elif args.draw_api == "pygame":
        run_pygame(GRAPH_FACTORIES[args.graph], args.graph_filename, args.width, args.height)


if __name__ == '__main__':
    main()
