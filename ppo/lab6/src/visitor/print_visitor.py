from typing import List

from tokenizer.tokens import Token, Operation, Brace, NumberToken
from visitor.visitor import TokenVisitor


class PrintVisitor(TokenVisitor):
    def visitNumber(self, token: NumberToken) -> None:
        print(str(token), end='')

    def visitBrace(self, token: Brace) -> None:
        print(str(token), end='')

    def visitOperation(self, token: Operation) -> None:
        print(str(token), end='')

    def visitList(self, tokens: List[Token]) -> None:
        for t in tokens:
            print(str(t), end='')
            print(" ", end='')
        print()
