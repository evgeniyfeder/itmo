from common.db_driver import PSQLDbDriver
from datetime import datetime
import psycopg2
import logging
from common.db_driver import PSQLSettings
from turnstile.db_objects import TurnstileStatus, TurnstileEvent

logger = logging.getLogger(__name__)


class TurnstileDbDriver(PSQLDbDriver):
    def __init__(self, con_settings: PSQLSettings):
        super().__init__(con_settings)

    def _add_turnstile_event(self, user_id: int, event_time: datetime, event_type: TurnstileStatus):
        new_user_event_id = self.get_max_user_event_id(user_id) + 1

        self.insert_event(user_id, new_user_event_id)

        query = "INSERT INTO TurnstileEvents(user_id, event_id, event_timestamp, event_type)" \
                f"  VALUES ({user_id}, {new_user_event_id}, \'{event_time}\', \'{event_type.value}\')"

        try:
            self.execute_query(query, lambda cursor: None)
        except (Exception, psycopg2.DatabaseError) as error:
            logger.error(error)

    def add_enter_event(self, user_id: int, enter_time: datetime):
        self._add_turnstile_event(user_id, enter_time, TurnstileStatus.enter)

    def add_exit_event(self, user_id: int, enter_time: datetime):
        self._add_turnstile_event(user_id, enter_time, TurnstileStatus.exit)

    def get_last_turnstile_event(self, user_id: int) -> TurnstileEvent:
        query = "SELECT " \
                "   user_id, event_id, event_timestamp, event_type " \
                "FROM " \
                "   TurnstileEvents " \
                "WHERE " \
                "   event_timestamp = " \
                f"      (SELECT max(event_timestamp) FROM TurnstileEvents WHERE user_id={user_id})"

        res = self.execute_query(query, lambda cursor: cursor.fetchone())
        return TurnstileEvent(user_id=res[0],
                              event_id=res[1],
                              event_timestamp=res[2],
                              event_type=TurnstileStatus(res[3])) \
            if res is not None else None
