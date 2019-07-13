open Data;;
open Printf;;

let (>>) x f = f x;;

let parse_str parser = (fun s -> s >> Lexing.from_string >> parser Lexer.main);;
let parse_expr = parse_str Parser.main;;

(*let (ic,oc) = (open_in "input.txt", open_out "output.txt");;*)

let buf = Buffer.create 1024;;
try
  while true do
    let line = input_line stdin in
    if (line <> "") then begin
      Buffer.add_string buf " ";
      Buffer.add_string buf line
    end;
  done;
with
  End_of_file -> ();
;;

printf "%s" (tree_to_string (parse_expr (Buffer.contents buf)));;
