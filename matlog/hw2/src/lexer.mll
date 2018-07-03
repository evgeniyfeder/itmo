{
open Parser
}

let variable = ['A' - 'Z']+ ['A' - 'Z' '0' - '9']*
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
	| "|-"					{ DISP }
  | eof           { EOF }
