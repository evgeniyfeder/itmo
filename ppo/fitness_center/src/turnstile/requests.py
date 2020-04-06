import attr
from datetime import datetime
from src.common.requests import AbstractCommand


@attr.s(auto_attribs=True)
class EnterCommand(AbstractCommand):
    user_id: int
    enter_time: datetime


@attr.s(auto_attribs=True)
class ExitCommand(AbstractCommand):
    user_id: int
    exit_time: datetime