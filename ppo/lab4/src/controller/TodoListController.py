from model.TodoListSqliteDao import TodoListSqliteDao
from view.TodoListViewer import TodoListViewer

from fastapi import FastAPI, Form
from starlette.requests import Request
from starlette.responses import Response
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
    return Response()


@app.post("/remove_list")
def remove_list(list_id=Form(...)):
    logger.debug(f"Removing list with id='{list_id}'")
    app.state.dao.remove_todolist(list_id)
    return Response()


@app.post("/add_task")
def add_task(list_id=Form(...), name=Form(...), desc=Form(...)):
    logger.debug(f"Add task with name='{name}' and desc='{desc}' to list with id='{list_id}'")
    app.state.dao.add_task(name, desc, list_id)
    return Response()
