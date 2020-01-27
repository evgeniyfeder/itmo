import importlib
import collections
import time
import types
import inspect


def profile_dec(func, work_duration, calls_count, indent, cls_name=''):
    def wrapper(*args, **kwargs):
        func_name = func.__name__ if cls_name == '' else cls_name + '.' + func.__name__
        print('{}{}'.format(' ' * indent[0], func_name))
        indent[0] += 2

        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()

        calls_count[func_name] += 1
        work_duration[func_name] += end - start
        indent[0] -= 2
        return result

    return wrapper


class Profiler:
    SEPARATOR = '============================'

    def _decorate_module(self, module, decorator, prefix=''):
        for name in dir(module):
            try:
                module_obj = getattr(module, name)

                if inspect.isfunction(module_obj):
                    setattr(module, name,
                            decorator(module_obj, self.work_duration, self.calls_count, self.indent, prefix))
                elif inspect.isclass(module_obj) and not name.startswith("__"):
                    new_prefix = name if prefix == '' else prefix + '.' + name
                    self._decorate_module(module_obj, decorator, new_prefix)
            except AttributeError:
                pass

    def __init__(self, module_name):
        self.work_duration = collections.defaultdict(int)
        self.calls_count = collections.defaultdict(int)
        self.indent = [0]

        self.module = importlib.import_module(module_name)
        self._decorate_module(self.module, profile_dec)

    def profile(self, function_module, profiling_function):
        print('Tree:')
        getattr(importlib.import_module(function_module), profiling_function)()
        print(Profiler.SEPARATOR)

        print('Time:')
        for func, duration in self.work_duration.items():
            print(f"{func}: {duration} s.")
        print(Profiler.SEPARATOR)

        print('Calls count')
        for func, count in self.calls_count.items():
            print(f"{func}: {count} time(s)")
        print(Profiler.SEPARATOR)

        print('Average time:')
        for func, duration in self.work_duration.items():
            print("{}: {} s.".format(func, duration / self.calls_count[func]))
