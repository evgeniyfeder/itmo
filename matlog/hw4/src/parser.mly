%token <int> NUM
%token EOF

%start main
%type <int list> main

%%

main:
  numbers           { $1 }

numbers:
  NUM                   { [$1] }
  | NUM numbers         { $1 :: $2 }
