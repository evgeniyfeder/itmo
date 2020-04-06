from enum import Enum
import attr
from datetime import datetime


class TurnstileStatus(Enum):
    enter = "enter"
    exit = "exit"


@attr.s(auto_attribs=True)
class TurnstileEvent:
    user_id: int
    event_id: int
    event_timestamp: datetime
    event_type: TurnstileStatus
