from starlette.templating import Jinja2Templates


class TodoListViewer:
    def __init__(self, templates_path: str):
        self.templates = Jinja2Templates(directory=templates_path)

    def get_homepage(self, request, todolist):
        return self.templates.TemplateResponse('index.html', {'request': request, 'todolist': todolist})
