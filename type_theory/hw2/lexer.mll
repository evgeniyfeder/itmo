{
open Parser
}

let variable = ['a' - 'z'] + ['a' - 'z' '0' - '9' '\'']*
let whitespace = [' ' '\t' '\n']

rule main = parse
   | whitespace    { main lexbuf }
   | variable as v { VAR(v) }
   | "("           { OPEN }
   | ")"           { CLOSE }
   | "."			  	 { POINT }
   | "\\"          { LAMBDA }
   | eof           { EOF }
