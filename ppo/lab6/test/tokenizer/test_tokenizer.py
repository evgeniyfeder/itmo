import pytest
from tokenizer.tokenizer import Tokenizer
from tokenizer.tokens import NumberToken, \
    PlusToken, MinusToken, MulToken, DivToken, \
    LeftBrace, RightBrace


@pytest.fixture()
def tokenizer():
    return Tokenizer()


def test_simple(tokenizer):
    assert tokenizer.tokenize("1+2") == [NumberToken(1), PlusToken(), NumberToken(2)]

def test_middle(tokenizer):
    assert tokenizer.tokenize("1+2*2") == [NumberToken(1), PlusToken(), NumberToken(2), MulToken(), NumberToken(2)]


def test_space(tokenizer):
    assert tokenizer.tokenize("   1 +2   ") == [NumberToken(1), PlusToken(), NumberToken(2)]


def test_brackets(tokenizer):
    assert tokenizer.tokenize(" (  1 +2  ) ") == [LeftBrace(), NumberToken(1), PlusToken(), NumberToken(2),
                                                  RightBrace()]


def test_incorrect(tokenizer):
    with pytest.raises(RuntimeError):
        tokenizer.tokenize(" (  1 +2  a) ")
