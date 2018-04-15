%{
  open Data;;
%}

%token <string> VAR
%token IMPL AND OR NOT
%token OPEN CLOSE
%token DISP COMMA
%token EOF
%right IMPL
%left OR
%left AND
%nonassoc NOT

%start main
%type <Data.tree> main

%start head
%type <Data.tree list> head
%%

main:
  expr EOF           { $1 }
expr:
  VAR                { Var ($1) }
  | OPEN expr CLOSE  { $2 }
  | NOT expr         { Neg ($2) }
  | expr IMPL expr   { Binop (Impl, $1, $3) }
  | expr AND expr    { Binop (Conj, $1, $3) }
  | expr OR expr     { Binop (Disj, $1, $3) }


head:
	exprs DISP expr EOF { $1 }
	| DISP expr EOF { [] }
exprs:
	expr { [ $1 ] }
	| expr COMMA exprs { $1 :: $3 }
