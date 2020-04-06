from common.db_driver import PSQLDbDriver
from datetime import datetime, timedelta
import psycopg2
from common.db_driver import PSQLSettings
from turnstile.db_objects import TurnstileEvent, TurnstileStatus
from collections import defaultdict
import calendar


class ReportDbDriver(PSQLDbDriver):
    def __init__(self, con_settings: PSQLSettings):
        super().__init__(con_settings)

    # average time of fitness house visiting and average number of visiting per human
    def avg_visit_duration_and_count(self, from_date: datetime):
        query = "SELECT user_id, event_id, event_timestamp, event_type " \
                "FROM " \
                "   TurnstileEvents " \
                "WHERE " \
                f"  event_timestamp >= '{from_date}' " \
                f"ORDER BY " \
                f"   event_timestamp"

        with self.con.cursor() as cur:
            cur.execute(query)

            is_enter = defaultdict(lambda : True)
            start_time = defaultdict(datetime)

            sum_time = timedelta()
            cnt = defaultdict(int)
            for row in cur:
                event = TurnstileEvent(user_id=row[0], event_id=row[1],
                                       event_timestamp=row[2], event_type=TurnstileStatus(row[3]))

                if is_enter[event.user_id]:
                    assert event.event_type == TurnstileStatus.enter
                    start_time[event.user_id] = event.event_timestamp
                    is_enter[event.user_id] = False
                else:
                    assert event.event_type == TurnstileStatus.exit
                    sum_time += (event.event_timestamp - start_time[event.user_id])
                    cnt[event.user_id] += 1
                    is_enter[event.user_id] = True

        if sum(cnt.values()) != 0:
            return {"avg_time_s": sum_time.seconds / sum(cnt.values()), "avg_cnt": sum(cnt.values()) / len(cnt)}
        else:
            return None

    def get_earliest_date(self):
        query = "SELECT min(event_timestamp) " \
                "FROM " \
                "   TurnstileEvents"
        return self.execute_query(query, lambda cursor: cursor.fetchone())[0]

    # day from monday -> cnt of visit
    def all_visit_by_day(self, from_date: datetime):
        query = "SELECT user_id, event_id, event_timestamp, event_type " \
                "FROM " \
                "   TurnstileEvents " \
                "WHERE " \
                f"  event_timestamp >= '{from_date}' " \
                f"ORDER BY " \
                f"   event_timestamp"

        with self.con.cursor() as cur:
            cur.execute(query)

            days = list(calendar.day_name)
            stat_day = {d: 0 for d in days}
            for row in cur:
                event = TurnstileEvent(user_id=row[0], event_id=row[1],
                                       event_timestamp=row[2], event_type=TurnstileStatus(row[3]))
                if event.event_type == TurnstileStatus.enter:
                    stat_day[days[event.event_timestamp.weekday()]] += 1
        return stat_day
