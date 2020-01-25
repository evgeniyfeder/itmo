import attr
from enum import Enum

class TaskStatus(Enum):
    OPENED = 1
    CLOSED = 2


@attr.s(auto_attribs=True)
class TodoTask:
    id: int
    name: str
    desc: str
    status: TaskStatus
    list_id: int


@attr.s(auto_attribs=True)
class TodoList:
    id: int
    name: str
    desc: str