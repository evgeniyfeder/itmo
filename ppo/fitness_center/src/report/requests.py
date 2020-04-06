import attr
from datetime import datetime
from src.common.requests import AbstractCommand, AbstractQuery


@attr.s(auto_attribs=True)
class GetAvgVisitDurationAndCntQuery(AbstractQuery):
    from_date: datetime


@attr.s(auto_attribs=True)
class GetStatByDayQuery(AbstractQuery):
    from_date: datetime


@attr.s(auto_attribs=True)
class GetEarliestEventQuery(AbstractQuery):
    pass
