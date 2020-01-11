import pytest

from tokenizer.tokenizer import Tokenizer
from tokenizer.tokens import NumberToken, \
    PlusToken, MinusToken, MulToken, DivToken, \
    LeftBrace, RightBrace
from visitor.calc_visitor import CalcVisitor


@pytest.fixture()
def calc_visitor():
    return CalcVisitor()


def test_simple(calc_visitor):
    tokens = [NumberToken(1), NumberToken(2), PlusToken()]
    calc_visitor.visit(tokens)
    assert calc_visitor.result == 3


def test_priority(calc_visitor):
    tokens = [NumberToken(1), NumberToken(2), NumberToken(2), MulToken(), PlusToken()]
    calc_visitor.visit(tokens)
    assert calc_visitor.result == 5


def test_brackets(calc_visitor):
    tokens = [LeftBrace(), NumberToken(1), NumberToken(2), PlusToken(), RightBrace(), NumberToken(2), MulToken()]
    with pytest.raises(RuntimeError):
        calc_visitor.visit(tokens)