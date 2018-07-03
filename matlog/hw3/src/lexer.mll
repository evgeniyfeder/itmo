{
open Parser;;
}

let variable = ['A' - 'Z'] + ['A' - 'Z' '0' - '9']*
let whitespace = [' ' '\t' '\n' '\r']

rule main = parse
	| whitespace    { main lexbuf }
  | variable as v { VAR(v) }
  | "->"          { IMPL }
  | "&"           { AND }
  | "|"           { OR }
  | "!"           { NOT }
  | "("           { OPEN }
  | ")"           { CLOSE }
	| ","						{ COMMA }
	| "|="					{ GENERAL }
  | eof           { EOF }

and lemma a b = parse
	| whitespace    { lemma a b lexbuf }
	| "->"          { IMPL }
	| "&"           { AND }
	| "|"           { OR }
	| "!"           { NOT }
	| "("           { OPEN }
	| ")"           { CLOSE }
	| "A"						{ EXPR(a) }
	| "B"						{ EXPR(b) }
	| eof           { EOF }
