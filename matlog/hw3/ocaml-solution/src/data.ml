open Printf;;

(* Operations *)
type op = Conj | Disj | Impl;;

let op_to_string = function
	| Conj -> "&"
	| Disj -> "|"
	| Impl -> "->";;

(* Parser tree *)
type tree =
	| Binop of op * tree * tree
  | Neg of tree
  | Var of string;;

let rec tree_to_string = function
  | Binop (op, x, y) -> "(" ^ (tree_to_string x) ^ (op_to_string op) ^ (tree_to_string y) ^ ")"
	| Neg (x) -> "(!" ^ (tree_to_string x) ^ ")"
	| Var (x) -> x
;;

let rec print_tree_list oc arr = match arr with
	| [] 			-> ()
	| x :: xs ->
		fprintf oc ",%s" (tree_to_string x);
		print_tree_list oc xs
;;


module SS = Set.Make(String);;
let rec get_variables = function
  | Binop (op, x, y) -> (SS.union (get_variables x) (get_variables y))
	| Neg (x) -> (get_variables x)
	| Var (x) -> SS.singleton x
;;

let print_set s =
     SS.iter print_endline s;;
