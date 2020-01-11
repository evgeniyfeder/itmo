import abc
import attr


@attr.s(auto_attribs=True, hash=True)
class Token(metaclass=abc.ABCMeta):
    @abc.abstractmethod
    def accept(self, visitor) -> None:
        raise NotImplementedError


@attr.s(auto_attribs=True, hash=True)
class NumberToken(Token):
    number: int

    def __str__(self):
        return f"NUMBER({self.number})"

    def accept(self, visitor) -> None:
        visitor.visit(self)


### Brackets
class Brace(Token):
    def accept(self, visitor) -> None:
        visitor.visit(self)


class LeftBrace(Brace):
    def __str__(self):
        return "LEFT"


class RightBrace(Brace):
    def __str__(self):
        return "RIGHT"


### Operations
class Operation(Token):
    def accept(self, visitor) -> None:
        visitor.visit(self)


class PlusToken(Operation):
    def __str__(self):
        return "PLUS"


class MinusToken(Operation):
    def __str__(self):
        return "MINUS"


class MulToken(Operation):
    def __str__(self):
        return "MUL"


class DivToken(Operation):
    def __str__(self):
        return "DIV"
