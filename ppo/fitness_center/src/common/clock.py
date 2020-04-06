import abc
import datetime


class AbstractClock(metaclass=abc.ABCMeta):
    def now(self) -> datetime.datetime:
        raise NotImplementedError()


class NowClock(AbstractClock):
    def now(self) -> datetime.datetime:
        return datetime.datetime.now()


class ConstantClock(AbstractClock):
    def __init__(self, now_time: datetime.datetime):
        self.now_time = now_time

    def now(self) -> datetime.datetime:
        return self.now_time
