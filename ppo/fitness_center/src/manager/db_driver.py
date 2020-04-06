from common.db_driver import PSQLDbDriver
from datetime import datetime
import psycopg2
import logging
from common.db_driver import PSQLSettings
from manager.db_objects import UserSubscription

logger = logging.getLogger(__name__)

class ManagerDbDriver(PSQLDbDriver):
    def __init__(self, con_settings: PSQLSettings):
        super().__init__(con_settings)

    def update_subscription_event(self, user_id: int, end_date: datetime):
        new_user_event_id = self.get_max_user_event_id(user_id) + 1

        self.insert_event(user_id, new_user_event_id)

        query = "INSERT INTO UpdateSubscriptionEvents(user_id, event_id, end_date)" \
                f"  VALUES ({user_id}, {new_user_event_id}, \'{end_date}\')"

        try:
            self.execute_query(query, lambda cursor: None)
        except (Exception, psycopg2.DatabaseError) as error:
            logger.error(error)