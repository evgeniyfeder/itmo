(* Parser tree *)
type tree =
	| Applic of tree * tree
   | Abstr  of tree * tree 
   | Var    of string;;

let rec tree_to_string = function
   | Applic (x, y) -> "(" ^ (tree_to_string x) ^ " " ^ (tree_to_string y) ^ ")"
	| Abstr (var, x) -> "(\\" ^ (tree_to_string var) ^ "." ^ (tree_to_string x) ^ ")"
	| Var (x) -> x;;
