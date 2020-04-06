from starlette.config import Config
from fastapi import FastAPI
from fastapi.responses import JSONResponse, Response
import logging
from datetime import datetime

from manager.requests import UpdateSubscriptionCommand, GetUserInformationQuery
from manager.db_driver import ManagerDbDriver
from manager.handler import ManagerHandler

from common.db_driver import PSQLSettings


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
    db = ManagerDbDriver(PSQLSettings(dbname=DBNAME, user=USER,
                                        password=PASS, host=HOST, schema_file=SCHEMA))
    app.state.handler = ManagerHandler(db)


@app.on_event('shutdown')
def shutdown_event():
    app.state.handler.close()


@app.post('/update_subscription')
def update_subscription(user_id: int, until_date: datetime):
    logger.info(f"User with id {user_id} update subscription until {until_date}")
    command = UpdateSubscriptionCommand(user_id, until_date)
    app.state.handler.handle_command(command)
    return Response(status_code=200)


@app.get('/get_user')
def get_user(user_id: int):
    logger.info(f"Get subscription of {user_id} user")
    query = GetUserInformationQuery(user_id)
    user = app.state.handler.handle_query(query)

    if user:
        return JSONResponse(status_code=200, content={"update_time": str(user.end_date)})
    else:
        return JSONResponse(status_code=204)
