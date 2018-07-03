type token =
  | VAR of (string)
  | EXPR of (Data.tree)
  | IMPL
  | AND
  | OR
  | NOT
  | OPEN
  | CLOSE
  | GENERAL
  | COMMA
  | EOF

val main :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> Data.tree
val head :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> (Data.tree list) * Data.tree
