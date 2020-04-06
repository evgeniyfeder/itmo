from starlette.config import Config
from fastapi import FastAPI
from fastapi.responses import Response
import logging

from turnstile.requests import EnterCommand, ExitCommand
from turnstile.db_driver import TurnstileDbDriver
from turnstile.handler import TurnstileHandler

from common.db_driver import PSQLSettings
from common.clock import NowClock

config = Config('.env')

app = FastAPI()
logger = logging.getLogger(__name__)

DBNAME = config.get('DBNAME')
USER = config.get('USER')
PASS = config.get('PASS')
HOST = config.get('HOST')
SCHEMA = config.get('SCHEMA')


@app.on_event('startup')
def startup_event():
    db = TurnstileDbDriver(PSQLSettings(dbname=DBNAME, user=USER,
                                        password=PASS, host=HOST, schema_file=SCHEMA))
    app.state.handler = TurnstileHandler(db)
    app.state.clock = NowClock()


@app.on_event('shutdown')
def shutdown_event():
    app.state.handler.close()


@app.post('/enter')
def enter_event(user_id: int):
    logger.info(f"User with id {user_id} have entered yet")
    command = EnterCommand(user_id, app.state.clock.now())
    app.state.handler.handle_command(command)
    return Response(status_code=200)


@app.post('/exit')
def enter_event(user_id: int):
    logger.info(f"User with id {user_id} have exited yet")
    command = ExitCommand(user_id, app.state.clock.now())
    app.state.handler.handle_command(command)
    return Response(status_code=200)
