from common.handler import AbstractHandler
from common.requests import AbstractQuery
from turnstile.db_driver import TurnstileDbDriver
from turnstile.db_objects import TurnstileStatus
from turnstile.requests import EnterCommand, ExitCommand, AbstractCommand
from fastapi.exceptions import HTTPException

class TurnstileHandler(AbstractHandler):
    def handle_query(self, query: AbstractQuery):
        pass

    def __init__(self, db: TurnstileDbDriver):
        self.db = db

    def handle_command(self, command: AbstractCommand):
        if isinstance(command, EnterCommand):
            last_enter = self.db.get_last_turnstile_event(command.user_id)
            if last_enter is not None and last_enter.event_type == TurnstileStatus.enter:
                raise HTTPException(status_code=400, detail="Can't enter after enter")

            last_sub = self.db.get_user_subscription_event(command.user_id)
            if last_sub is not None and last_sub.end_date < command.enter_time:
                raise HTTPException(status_code=400, detail="Can't enter without subscription")

            self.db.add_enter_event(command.user_id, command.enter_time)

        elif isinstance(command, ExitCommand):
            last_enter = self.db.get_last_turnstile_event(command.user_id)
            if last_enter is None or last_enter.event_type == TurnstileStatus.exit:
                raise HTTPException(status_code=400, detail="Can't exit without enter")

            self.db.add_exit_event(command.user_id, command.exit_time)

    def close(self):
        self.db.close()
