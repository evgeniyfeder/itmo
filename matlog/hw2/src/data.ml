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
	| x :: [] -> fprintf oc "%s" (tree_to_string x)
	| [] 			-> ()
	| x :: xs ->
		fprintf oc "%s," (tree_to_string x);
		print_tree_list oc xs
;;


(* Annotation *)
type annotation =
	| Axiom of int
	| Assumption of int
	| ModusPonus of int * int
	| Incorrect
;;

let annotation_to_string = function
	| Axiom i					  -> "(Сх. акс. " ^ string_of_int i ^ ")"
	| Assumption i 			-> "(Предп. " ^ string_of_int i ^ ")"
	| ModusPonus (i, j) -> "(M.P. " ^ string_of_int i ^ ", " ^ string_of_int j ^ ")"
	| Incorrect 				-> "(Не доказано)"
;;

(* Working with files *)
let read_file filename =
 let lines = ref [] in
 	let in_file = open_in filename in
  try
    while true do
      let l = input_line in_file in
      	lines := l :: !lines
    done;
    !lines
  with End_of_file ->
   close_in in_file;
   List.rev !lines
;;
