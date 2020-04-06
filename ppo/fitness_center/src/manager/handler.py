from common.handler import AbstractHandler
from common.requests import AbstractQuery, AbstractCommand
from manager.db_driver import ManagerDbDriver
from manager.requests import GetUserInformationQuery, UpdateSubscriptionCommand
from fastapi.exceptions import HTTPException


class ManagerHandler(AbstractHandler):
    def __init__(self, db: ManagerDbDriver):
        self.db = db

    def handle_command(self, command: AbstractCommand):
        if isinstance(command, UpdateSubscriptionCommand):
            last_sub = self.db.get_user_subscription_event(command.user_id)
            if last_sub is not None and last_sub.end_date > command.until_date:
                raise HTTPException(status_code=400, detail="Can't update subscription earlier than now")

            self.db.update_subscription_event(command.user_id, command.until_date)

    def handle_query(self, query: AbstractQuery):
        if isinstance(query, GetUserInformationQuery):
            return self.db.get_user_subscription_event(query.user_id)

    def close(self):
        self.db.close()
