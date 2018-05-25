type token =
  | NUM of (int)
  | EOF

val main :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> int list
