import argparse

from tokenizer.tokenizer import Tokenizer
from visitor.rpn_visitor import RpnVisitor
from visitor.calc_visitor import CalcVisitor
from visitor.print_visitor import PrintVisitor


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("expr", metavar="EXPR", help="Expression to parse")
    args = parser.parse_args()

    print(f"Input string: {args.expr}")

    tokenizer = Tokenizer()
    tokens = tokenizer.tokenize(args.expr)
    print(f"Tokenized string: {tokens}")

    rpn_visitor = RpnVisitor()
    rpn_visitor.visit(tokens)
    print(f"Tokens in RPN forn: {rpn_visitor.result}")

    calc_visitor = CalcVisitor()
    calc_visitor.visit(rpn_visitor.result)
    print(f"Result for expression: {calc_visitor.result}")

    print_visitor = PrintVisitor()
    print(f"Printed version of RPN form: ")
    print_visitor.visit(rpn_visitor.result)


if __name__ == '__main__':
    main()
