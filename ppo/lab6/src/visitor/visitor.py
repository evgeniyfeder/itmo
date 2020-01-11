import abc
from tokenizer.tokens import Brace, NumberToken, Operation, Token
from typing import List


class TokenVisitor(metaclass=abc.ABCMeta):
    def visit(self, token):
        if isinstance(token, NumberToken):
            self.visitNumber(token)
        elif isinstance(token, Operation):
            self.visitOperation(token)
        elif isinstance(token, Brace):
            self.visitBrace(token)
        elif isinstance(token, List):
            self.visitList(token)
        else:
            raise NotImplementedError

    @abc.abstractmethod
    def visitNumber(self, token: NumberToken) -> None:
        raise NotImplementedError

    @abc.abstractmethod
    def visitBrace(self, token: Brace) -> None:
        raise NotImplementedError

    @abc.abstractmethod
    def visitOperation(self, token: Operation) -> None:
        raise NotImplementedError

    @abc.abstractmethod
    def visitList(self, tokens: List[Token]) -> None:
        raise NotImplementedError
