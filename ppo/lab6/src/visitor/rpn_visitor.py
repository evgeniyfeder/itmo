from typing import List

from tokenizer.tokens import \
    NumberToken, Operation, Brace, \
    LeftBrace, RightBrace, \
    PlusToken, MinusToken, MulToken, DivToken, Token
from visitor.visitor import TokenVisitor


class RpnVisitor(TokenVisitor):
    def visitList(self, tokens: List[Token]) -> None:
        for t in tokens:
            t.accept(self)

        while len(self._stack) > 0:
            last_elem = self._stack[len(self._stack) - 1]
            self._stack.pop()

            if isinstance(last_elem, Operation):
                self._result.append(last_elem)
            else:
                raise RuntimeError("Not operation token in stack when token list is empty")

    @property
    def result(self):
        return self._result

    @staticmethod
    def _operation_priority(token: Operation) -> int:
        op_p_map = {
            PlusToken(): 1,
            MinusToken(): 1,
            MulToken(): 2,
            DivToken(): 2,
            LeftBrace(): 0
        }
        return op_p_map[token]

    def __init__(self):
        self._result = []
        self._stack = []

    def visitBrace(self, token: Brace) -> None:
        if isinstance(token, LeftBrace):
            self._stack.append(token)
        elif isinstance(token, RightBrace):
            while len(self._stack) > 0:
                last_elem = self._stack[len(self._stack) - 1]
                self._stack.pop()

                if isinstance(last_elem, LeftBrace):
                    return
                elif isinstance(last_elem, Operation):
                    self._result.append(last_elem)
                elif isinstance(last_elem, NumberToken):
                    raise RuntimeError(f"Unexpected number in stack: {str(self._stack)}")

    def visitOperation(self, token: Operation) -> None:
        while len(self._stack) > 0:
            last_elem = self._stack[len(self._stack) - 1]

            if self._operation_priority(token) <= self._operation_priority(last_elem):
                self._stack.pop()
                self._result.append(last_elem)
            else:
                break
        self._stack.append(token)

    def visitNumber(self, token: NumberToken) -> None:
        self._result.append(token)


