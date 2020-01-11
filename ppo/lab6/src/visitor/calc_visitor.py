from typing import List

from tokenizer.tokens import \
    Token, Operation, Brace, NumberToken, \
    PlusToken, MinusToken, MulToken, DivToken
from visitor.visitor import TokenVisitor
import operator

class CalcVisitor(TokenVisitor):
    def __init__(self):
        self._stack = []

    @property
    def result(self):
        assert len(self._stack) == 1 and isinstance(self._stack[0], NumberToken), "There is no result"
        return self._stack[0].number

    def visitNumber(self, token: NumberToken) -> None:
        self._stack.append(token)

    def visitBrace(self, token: Brace) -> None:
        raise RuntimeError("In RPN there are no brackets")

    TOKEN_OPERATIONS = {
        PlusToken(): operator.add,
        MinusToken(): operator.sub,
        MulToken(): operator.mul,
        DivToken(): operator.floordiv
    }

    def _token_op_do(self, token: Operation, a, b):
        assert isinstance(a, NumberToken) and isinstance(b, NumberToken), "In stack need to bee numbertokens"
        return self.TOKEN_OPERATIONS[token](a.number, b.number)

    def visitOperation(self, token: Operation) -> None:
        assert len(self._stack) >= 2, "There is no 2 arguments for operation"
        y = self._stack.pop()
        x = self._stack.pop()

        self._stack.append(NumberToken(self._token_op_do(token, x, y)))

    def visitList(self, tokens: List[Token]) -> None:
        for t in tokens:
            t.accept(self)