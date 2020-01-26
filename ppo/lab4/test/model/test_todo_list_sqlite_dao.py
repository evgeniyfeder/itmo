from model.todo_list_sqlite_dao import TodoListSqliteDao
from model.model_objects import TaskStatus

import pytest
import tempfile


@pytest.fixture()
def db():
    with tempfile.TemporaryDirectory() as tmpdirname:
        print('created temporary directory', tmpdirname)
        db = TodoListSqliteDao(f"{tmpdirname}/test.sqlite")
        yield db


def test_todolists(db: TodoListSqliteDao):
    assert len(db.get_all_todos()) == 0

    db.add_todolist("test_name", "test_desc")
    todos = db.get_all_todos()
    assert len(todos) == 1
    assert len(todos[0][1]) == 0
    assert todos[0][0].name == "test_name"
    assert todos[0][0].desc == "test_desc"

    db.add_todolist("test_name_2", "test_desc_2")
    todos = db.get_all_todos()
    assert len(todos) == 2
    assert todos[0][0].name == "test_name"
    assert todos[0][0].desc == "test_desc"
    assert todos[1][0].name == "test_name_2"
    assert todos[1][0].desc == "test_desc_2"

    db.remove_todolist(todos[0][0].id)

    todos = db.get_all_todos()
    assert len(todos) == 1
    assert len(todos[0][1]) == 0
    assert todos[0][0].name == "test_name_2"
    assert todos[0][0].desc == "test_desc_2"


def test_tasks(db: TodoListSqliteDao):
    assert len(db.get_all_todos()) == 0

    db.add_todolist("test_name", "test_desc")
    todos = db.get_all_todos()
    assert len(todos) == 1
    assert len(todos[0][1]) == 0
    assert todos[0][0].name == "test_name"
    assert todos[0][0].desc == "test_desc"

    db.add_task("task_name_2", "task_desc_2", todos[0][0].id)
    todos = db.get_all_todos()
    assert len(todos) == 1
    assert len(todos[0][1]) == 1
    assert todos[0][0].name == "test_name"
    assert todos[0][0].desc == "test_desc"
    assert todos[0][1][0].name == "task_name_2"
    assert todos[0][1][0].desc == "task_desc_2"
    assert todos[0][1][0].status == TaskStatus.OPENED

    db.change_task_status(todos[0][1][0].id, TaskStatus.CLOSED)

    todos = db.get_all_todos()
    assert todos[0][1][0].status == TaskStatus.CLOSED