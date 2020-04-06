from starlette.config import Config
from fastapi import FastAPI
from fastapi.responses import JSONResponse
import logging

from report.requests import GetStatByDayQuery, GetAvgVisitDurationAndCntQuery, GetEarliestEventQuery
from report.db_driver import ReportDbDriver
from report.handler import ReportHandler

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
    db = ReportDbDriver(PSQLSettings(dbname=DBNAME, user=USER,
                                     password=PASS, host=HOST, schema_file=SCHEMA))
    app.state.handler = ReportHandler(db)
    app.state.clock = NowClock()
    app.state.last_statistic = None


@app.on_event('shutdown')
def shutdown_event():
    app.state.handler.close()


@app.post('/report')
def enter_event():
    logger.info(f"Get statistic")

    stat = {"start_time": app.state.handler.handle_query(GetEarliestEventQuery())}

    freq_stat = app.state.handler.handle_query(GetAvgVisitDurationAndCntQuery(stat["start_time"]))
    if freq_stat:
        freq_stat["avg_time_s"] = str(freq_stat["avg_time_s"])
        stat["start_time"] = str(stat["start_time"])

        stat.update(freq_stat)
        stat["per_day_stat"] = app.state.handler.handle_query(GetStatByDayQuery(stat["start_time"]))
        return JSONResponse(status_code=200, content=stat)
    else:
        return JSONResponse(status_code=204)
