import attr
from datetime import datetime
from src.common.requests import AbstractCommand, AbstractQuery


@attr.s(auto_attribs=True)
class UpdateSubscriptionCommand(AbstractCommand):
    user_id: int
    until_date: datetime


@attr.s(auto_attribs=True)
class GetUserInformationQuery(AbstractQuery):
    user_id: int
