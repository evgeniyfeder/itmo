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
(*(\f.\x.f (f x)) (\f.\x.f (f x))*)

let in_tree = (parse_expr (Buffer.contents buf));;

let (cont, tree) = go_to_normal_form (to_de_bruijn_tree in_tree) in
  let cont_ref = ref cont in
    let tree_ref = ref tree in
      while (!cont_ref) do
        let (cont_while, tree_while) = go_to_normal_form !tree_ref in
          cont_ref := cont_while;
          tree_ref := tree_while;
      done;
      printf "%s\n" (tree_to_string (to_tree !tree_ref))
;;
(* let res = (go_to_normal_form in_tree);; *)
(*printf "%s" (db_tree_to_string (to_de_bruijn_tree in_tree));;*)
(* printf "%s\n" (db_tree_to_string res);; *)
(* printf "%s\n" (tree_to_string (to_tree res));; *)
