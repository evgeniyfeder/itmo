open Data;;
open Buffer;;
open Printf;;

let (ic,oc) = (open_in "input.txt", open_out "output.txt");;

(*** Utilities ***)
(* Shortcut for calling parser *)
let (>>) x f = f x;;

let parse_str parser = (fun s -> s >> Lexing.from_string >> parser Lexer.main);;
let parse_head head = parse_str Parser.head head;;
let parse_expr expr = parse_str Parser.main expr;;

(* Working parts *)
let input = parse_head (input_line ic);;
let assumptions = fst input;;
let input_expr = snd input;;

let variables_set = get_variables input_expr;;
print_set variables_set;;


close_out oc;;
close_in ic;;
