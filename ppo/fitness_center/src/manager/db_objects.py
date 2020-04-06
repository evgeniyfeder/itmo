import attr
from datetime import datetime


@attr.s(auto_attribs=True)
class UserSubscription:
    user_id: int
    event_id: int
    end_date: datetime
