type token =
  | VAR of (string)
  | IMPL
  | AND
  | OR
  | NOT
  | OPEN
  | CLOSE
  | DISP
  | COMMA
  | EOF

val main :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> Data.tree
val head :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> (Data.tree list) * Data.tree
