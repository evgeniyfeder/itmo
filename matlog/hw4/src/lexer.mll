{
open Parser;;
}

let whitespace = [' ' '\t' '\n' '\r']
let number = ['0' - '9']+

rule main = parse
	| whitespace    { main lexbuf }
	| number  as n	{ NUM(int_of_string n) }
  | eof           { EOF }
