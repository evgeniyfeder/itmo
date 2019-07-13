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
(*(\f.\x.(f x)) (\f.\x.f (f x)) \f.(\x.f(x x))(\x.f(x x)) a \a. a' a z8'*)

let in_tree = (parse_expr (Buffer.contents buf));;
(* printf "%s\n" (tree_to_string in_tree);; *)
let (map_free, (eq_system, type_schema)) = (get_eq_system in_tree);;
(* printf "eq_system:%s\ntype_schema:%s\n///////////\n" (eq_system_to_string eq_system) (aterm_to_string type_schema);; *)

(* Hashtbl.iter ((fun key value -> printf "%s %s\n" key (string_of_int value))) map_free;; *)

try
  let unification_res = unification eq_system in
    (* printf "un_res:%s\n///////\n" (eq_system_to_string unification_res); *)
    (* printf "res:%s\n//////\n" (aterm_to_string (subst_eq_system type_schema (get_hashtbl_eq_system unification_res))); *)
    printf "%s" (generate_deduction_tree in_tree (get_hashtbl_eq_system unification_res) map_free)
with UniFail (s) -> printf "%s" s
