%{
  open Data;;
%}

%token <string> VAR
%token OPEN CLOSE
%token LAMBDA POINT
%token EOF
%nonassoc LAMBDA POINT

%start main 
%type <Data.tree> main

%%

main : expr EOF                     { $1 }
expr:  appl LAMBDA VAR POINT expr   { Applic($1, Abstr(Var($3), $5)) }
   | LAMBDA VAR POINT expr          { Abstr(Var($2), $4) }
   | appl                           { $1 }

appl:
     appl atom                      { Applic($1, $2) }
   | atom                           { $1 }

atom:
   OPEN expr CLOSE                  { $2 }
   | VAR                            { Var($1) }

