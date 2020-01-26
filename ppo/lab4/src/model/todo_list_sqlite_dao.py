import sqlite3
from typing import List, Tuple
from model.model_objects import TodoTask, TodoList, TaskStatus
from contextlib import closing
from model.todo_list_dao import TodoListDao


class TodoListSqliteDao(TodoListDao):
    CREATE_TODO_LIST = "CREATE TABLE IF NOT EXISTS TodoList" \
                       "(" \
                       "  id integer primary key autoincrement not null," \
                       "  name text not null," \
                       "  desc text not null" \
                       ")"

    CREATE_TODO_TASK = "CREATE TABLE IF NOT EXISTS TodoTask" \
                       "(" \
                       "  id integer primary key autoincrement not null," \
                       "  name text not null," \
                       "  desc text not null," \
                       "  status integer not null," \
                       "  list_id integer references TodoList(id)" \
                       ")"

    def _execute_query(self, query: str):
        with closing(sqlite3.connect(self.db_path)) as db_conn:
            with closing(db_conn.cursor()) as cur:
                cur.execute(query)
                db_conn.commit()

    def _init_db(self):
        self._execute_query(self.CREATE_TODO_LIST)
        self._execute_query(self.CREATE_TODO_TASK)

    def __init__(self, db_path: str):
        self.db_path = db_path

        self._init_db()

    def add_todolist(self, name: str, desc: str):
        self._execute_query("INSERT INTO TodoList(name, desc) VALUES ('{}', '{}');".format(name, desc))

    def add_task(self, name: str, desc: str, list_id: int):
        self._execute_query("INSERT INTO TodoTask(name, desc, status, list_id) VALUES ('{}', '{}', '{}', '{}');"
                            .format(name, desc, TaskStatus.OPENED.value, list_id))

    def get_all_todos(self) -> List[Tuple[TodoList, List[TodoTask]]]:
        with closing(sqlite3.connect(self.db_path)) as db_conn:
            with closing(db_conn.cursor()) as cur:
                lists = cur.execute("SELECT id, name, desc FROM TodoList")

                res = []
                for l in lists.fetchall():
                    tasks_res = []
                    for t in cur.execute(f"SELECT id, name, desc, status FROM TodoTask WHERE list_id = {l[0]}").fetchall():
                        tasks_res.append(TodoTask(id=t[0], name=t[1], desc=t[2], status=TaskStatus(t[3]), list_id=l[0]))
                    res.append((TodoList(l[0], l[1], l[2]), tasks_res))
        return res

    def remove_todolist(self, list_id: int):
        self._execute_query(f"DELETE FROM TodoList WHERE id = {list_id}")

    def change_task_status(self, task_id: int, status: TaskStatus):
        self._execute_query(f"UPDATE TodoTask SET status = {status.value} WHERE id = {task_id}")
