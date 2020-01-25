from typing import List, Tuple
from model.ModelObjects import TodoTask, TodoList
from abc import ABCMeta, abstractmethod


class TodoListDao(metaclass=ABCMeta):
    @abstractmethod
    def add_todolist(self, name: str, desc: str):
        raise NotImplementedError

    @abstractmethod
    def add_task(self, name: str, desc: str, list_id: int):
        raise NotImplementedError

    @abstractmethod
    def get_all_todos(self) -> List[Tuple[TodoList, List[TodoTask]]]:
        raise NotImplementedError

    @abstractmethod
    def remove_todolist(self, list_id: int):
        raise NotImplementedError

    @abstractmethod
    def mark_task_as_done(self, task_id: int):
        raise NotImplementedError
