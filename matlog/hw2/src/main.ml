open Data;;
open Buffer;;
open Printf;;
open Deduct;;
let (ic,oc) = (open_in "input.txt", open_out "output.txt");;

(* Parser function *)
let (>>) x f = f x;;

let parse_str parser = (fun s -> s >> Lexing.from_string >> parser Lexer.main);;
let parse_head head = parse_str Parser.head head;;
let parse_expr expr = parse_str Parser.main expr;;

let assump_parts = parse_head (input_line ic);;
let assump_list = (fst assump_parts);;
let assump_size = List.length assump_list;;
let rev_assump = (List.rev assump_list);;
let a = (List.hd rev_assump);;

let lines = ref [];;
try
  while true do
    let line = input_line ic in begin
      if (line <> "") then
        let l = parse_expr line in
    	    lines := l :: !lines
    end
  done;
with End_of_file ->
 close_in ic
;;
lines := List.rev !lines;;
let result = deduct assump_list !lines a;;

print_tree_list oc (List.rev (List.tl rev_assump));;
fprintf oc "|-(%s)->(%s)\n" (tree_to_string a) (tree_to_string (snd assump_parts));;
List.iter (fun x -> fprintf oc "%s\n" (tree_to_string x)) result;;

close_out oc;;
close_in ic;;
