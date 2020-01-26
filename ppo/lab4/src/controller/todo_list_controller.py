from model.todo_list_sqlite_dao import TodoListSqliteDao, TaskStatus
from view.todo_list_viewer import TodoListViewer

from fastapi import FastAPI, Form
from starlette.requests import Request
from starlette.responses import RedirectResponse
import logging

app = FastAPI()
logger = logging.getLogger(__name__)


@app.on_event("startup")
def startup_event():
    app.state.dao = TodoListSqliteDao("db.sqlite")
    app.state.viewer = TodoListViewer("templates")


@app.get("/")
def read_root(request: Request):
    res = app.state.dao.get_all_todos()
    return app.state.viewer.get_homepage(request, res)


@app.post("/add_list")
def add_list(name=Form(...), desc=Form(...)):
    logger.debug(f"Add list with name='{name}' and desc='{desc}'")
    app.state.dao.add_todolist(name, desc)
    return RedirectResponse(url="/", status_code=303)


@app.post("/remove_list")
def remove_list(list_id=Form(...)):
    logger.debug(f"Removing list with id='{list_id}'")
    app.state.dao.remove_todolist(list_id)
    return RedirectResponse(url="/", status_code=303)


@app.post("/add_task")
def add_task(list_id=Form(...), name=Form(...), desc=Form(...)):
    logger.debug(f"Add task with name='{name}' and desc='{desc}' to list with id='{list_id}'")
    app.state.dao.add_task(name, desc, list_id)
    return RedirectResponse(url="/", status_code=303)


@app.post("/do_task")
def remove_list(task_id=Form(...)):
    logger.debug(f"Changing status of task with id='{task_id}' for CLOSED")
    app.state.dao.change_task_status(task_id, TaskStatus.CLOSED)

    return RedirectResponse(url="/", status_code=303)
