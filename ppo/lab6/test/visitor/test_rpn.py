import pytest

from tokenizer.tokenizer import Tokenizer
from tokenizer.tokens import NumberToken, \
    PlusToken, MinusToken, MulToken, DivToken, \
    LeftBrace, RightBrace
from visitor.rpn_visitor import RpnVisitor


@pytest.fixture()
def rpn_visitor():
    return RpnVisitor()


def test_simple(rpn_visitor):
    tokens = [NumberToken(1), PlusToken(), NumberToken(2)]
    rpn_visitor.visit(tokens)
    assert rpn_visitor.result == [NumberToken(1), NumberToken(2), PlusToken()]


def test_priority(rpn_visitor):
    tokens = [NumberToken(1), PlusToken(), NumberToken(2), MulToken(), NumberToken(2)]
    rpn_visitor.visit(tokens)
    assert rpn_visitor.result == [NumberToken(1), NumberToken(2), NumberToken(2), MulToken(), PlusToken()]


def test_brackets(rpn_visitor):
    tokens = [LeftBrace(), NumberToken(1), PlusToken(), NumberToken(2), RightBrace(), MulToken(), NumberToken(2)]
    rpn_visitor.visit(tokens)
    assert rpn_visitor.result == [NumberToken(1), NumberToken(2), PlusToken(), NumberToken(2), MulToken()]

def test_bad_brackets(rpn_visitor):
    tokens = [LeftBrace(), NumberToken(1), PlusToken(), NumberToken(2), MulToken(), NumberToken(2)]
    with pytest.raises(RuntimeError):
        rpn_visitor.visit(tokens)
