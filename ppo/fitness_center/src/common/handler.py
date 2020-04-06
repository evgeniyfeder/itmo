import abc
from common.requests import AbstractCommand, AbstractQuery


class AbstractHandler(metaclass=abc.ABCMeta):
    def handle_command(self, command: AbstractCommand):
        raise NotImplementedError()

    def handle_query(self, query: AbstractQuery):
        raise NotImplementedError()

    def close(self):
        raise NotImplementedError()

