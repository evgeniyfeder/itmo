import time


class A:
    def f(self):
        time.sleep(2)

    @staticmethod
    def st():
        time.sleep(1)

    class B:
        @staticmethod
        def g():
            time.sleep(1)


def f():
    time.sleep(1)
    A.st()


def g():
    time.sleep(2)


def h():
    time.sleep(3)


def test():
    f()
    g()
    h()
    f()
    a = A()
    a.f()
    a.B.g()
