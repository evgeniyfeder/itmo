from common.handler import AbstractHandler
from common.requests import AbstractQuery
from report.db_driver import ReportDbDriver
from report.requests import GetAvgVisitDurationAndCntQuery, GetStatByDayQuery, GetEarliestEventQuery, \
    AbstractQuery, AbstractCommand
import calendar


class ReportHandler(AbstractHandler):
    def handle_query(self, query: AbstractQuery):
        if isinstance(query, GetAvgVisitDurationAndCntQuery):
            return self.db.avg_visit_duration_and_count(query.from_date)
        elif isinstance(query, GetStatByDayQuery):
            return self.db.all_visit_by_day(query.from_date)
        elif isinstance(query, GetEarliestEventQuery):
            return self.db.get_earliest_date()

    def __init__(self, db: ReportDbDriver):
        self.db = db

    def handle_command(self, command: AbstractCommand):
        pass

    def close(self):
        self.db.close()
