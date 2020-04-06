import attr
import psycopg2
import abc
import logging
from manager.db_objects import UserSubscription

logger = logging.getLogger(__name__)


class AbstractDbDriver(metaclass=abc.ABCMeta):
    def close(self):
        raise NotImplementedError()

    def get_max_user_event_id(self, user_id):
        raise NotImplementedError()

    def insert_event(self, user_id, event_id):
        raise NotImplementedError()


@attr.s(auto_attribs=True)
class PSQLSettings:
    dbname: str
    user: str
    password: str
    host: str
    schema_file: str = None


def is_cursor_not_empty(cursor):
    res = False
    for c in cursor:
        res = True
    return res


class PSQLDbDriver(AbstractDbDriver):

    def __init__(self, con_settings: PSQLSettings):
        super().__init__()

        logger.info(f"Connect to {con_settings.dbname} db")
        self.con = psycopg2.connect(dbname=con_settings.dbname,
                                    user=con_settings.user,
                                    password=con_settings.password,
                                    host=con_settings.host)

        self.con.autocommit = True

        if con_settings.schema_file:
            logger.info(f"Read schema from '{con_settings.schema_file}'")
            with self.con.cursor() as cur:
                with open(con_settings.schema_file, "r") as f:
                    cur.execute(f.read())

    def close(self):
        self.con.close()

    def execute_query(self, query: str, f):
        with self.con.cursor() as cursor:
            cursor.execute(query)
            res = f(cursor)

        return res

    def get_max_user_event_id(self, user_id):
        query = f"SELECT max(event_id) FROM Events WHERE user_id={user_id}"

        res = self.execute_query(query, lambda cursor: cursor.fetchone())
        return res[0] if res[0] is not None else -1

    def insert_event(self, user_id, event_id):
        query = f"INSERT INTO Events(user_id, event_id) VALUES ({user_id}, {event_id})"

        try:
            self.execute_query(query, lambda cursor: None)
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)

    def get_user_subscription_event(self, user_id: int) -> UserSubscription:
        query = "SELECT " \
                "   user_id, event_id, end_date " \
                "FROM " \
                "   UpdateSubscriptionEvents " \
                "WHERE " \
                "   end_date = " \
                f"      (SELECT max(end_date) FROM UpdateSubscriptionEvents WHERE user_id={user_id})"

        res = self.execute_query(query, lambda cursor: cursor.fetchone())
        return UserSubscription(user_id=res[0],
                                event_id=res[1],
                                end_date=res[2]) \
            if res is not None else None

