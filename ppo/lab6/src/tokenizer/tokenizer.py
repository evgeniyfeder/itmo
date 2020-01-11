from __future__ import annotations

import attr
import abc
from typing import List, Tuple, Optional, Union

from tokenizer.tokens import NumberToken, \
    DivToken, MinusToken, MulToken, PlusToken, \
    LeftBrace, RightBrace

from tokenizer.tokens import Token


class TokenizerState(metaclass=abc.ABCMeta):
    @abc.abstractmethod
    def handle(self, c: str) -> Tuple[List[Token], TokenizerState]:  # c - one char
        raise NotImplementedError


class StartState(TokenizerState):
    def handle(self, c: str) -> Tuple[Optional[List[Token]], Union[NumberState, StartState, ErrorState, EndState]]:
        if c is None:
            return None, Tokenizer.END_STATE

        operators = {
            '(': LeftBrace,
            ')': RightBrace,
            '/': DivToken,
            '-': MinusToken,
            '*': MulToken,
            '+': PlusToken,
        }

        if c in operators:
            return [operators[c]()], self
        elif c.isdigit():
            return None, NumberState(int(c))
        elif c == ' ':
            return None, self
        else:
            return None, ErrorState(f"unknown character {c}")


@attr.s(auto_attribs=True)
class NumberState(TokenizerState):
    acc: int

    def handle(self, c: str) -> Tuple[Optional[List[Token]], Union[NumberState, StartState]]:
        if c is not None and c.isdigit():
            self.acc = self.acc * 10 + int(c)
            return None, self
        else:
            tokens, state = Tokenizer.START_STATE.handle(c)

            result = [NumberToken(self.acc)]
            if tokens:
                result = result + tokens
            return result, state


@attr.s(auto_attribs=True)
class ErrorState(TokenizerState):
    msg: str

    def handle(self, c: str) -> Tuple[Optional[List[Token]], ErrorState]:
        return None, self


class EndState(TokenizerState):
    def handle(self, c: str) -> Tuple[Optional[List[Token]], EndState]:
        return None, self


class Tokenizer:
    START_STATE = StartState()
    END_STATE = EndState()

    def __init__(self):
        self._cur_state = Tokenizer.START_STATE
        self._token_list = []

    def process(self, c):
        tokens, self._cur_state = self._cur_state.handle(c)

        if tokens is not None:
            self._token_list = self._token_list + tokens

    def tokenize(self, string: str) -> List[Token]:
        assert self._cur_state == Tokenizer.START_STATE, "Tokenizer not in start state"

        for c in string:
            self.process(c)
        self.process(None)

        if self._cur_state != Tokenizer.END_STATE:
            if isinstance(self._cur_state, ErrorState):
                raise RuntimeError(f"Lexer error: {self._cur_state.msg}")
            else:
                raise RuntimeError("State need to be end state or error state")

        return self._token_list
