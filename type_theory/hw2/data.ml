open Printf;;


type tree =
	| Applic of tree * tree
  | Abstr  of string * tree
  | Var    of string
;;

let rec tree_to_string = function
	| Applic (x, y) -> "(" ^ (tree_to_string x) ^ " " ^ (tree_to_string y) ^ ")"
	| Abstr (var, x) -> "(\\" ^ var ^ "." ^ (tree_to_string x) ^ ")"
	| Var (x) -> x
;;

type de_bruijn_tree =
  | DbApplic  of de_bruijn_tree * de_bruijn_tree
  | DbAbstr   of de_bruijn_tree
  | FreeVar of string
  | RefVar of int
;;

let rec db_tree_to_string = function
	| DbApplic (x, y) -> "(" ^ (db_tree_to_string x) ^ " " ^ (db_tree_to_string y) ^ ")"
	| DbAbstr (x) -> "(\\." ^ (db_tree_to_string x) ^ ")"
	| FreeVar (str) -> str
	| RefVar (ind) -> string_of_int ind
;;

let to_de_bruijn_tree tree =
	let name_to_index = Hashtbl.create 1024 in
		let rec to_de_bruijn_tree' height tree = match tree with
			| Applic (x, y) -> DbApplic (to_de_bruijn_tree' (height + 1) x, to_de_bruijn_tree' (height + 1) y)
			| Abstr (var, x) ->
					Hashtbl.add name_to_index var height;
					let res = to_de_bruijn_tree' (height + 1) x in
						Hashtbl.remove name_to_index var;
						DbAbstr(res)
			| Var (x) ->
					match Hashtbl.find_opt name_to_index x with
						| Some res -> RefVar(height - res)
						| None -> FreeVar(x)
		in
			to_de_bruijn_tree' 0 tree
;;

let to_tree bt_tree =
	let cur_appl_index = ref 0 in
		let rec count_len_free_var = function
			| DbApplic (x, y) -> max (count_len_free_var x) (count_len_free_var y)
			| DbAbstr (x) -> (count_len_free_var x)
			| FreeVar (str) -> String.length str
			| RefVar (ind) -> 0
		in
			let template_name = String.make ((count_len_free_var bt_tree) + 1) 'a' in
				let appl_table = Hashtbl.create 1024 in
					let rec to_tree' height = function
						| DbApplic (x, y) -> Applic ((to_tree' (height + 1) x), (to_tree' (height + 1) y))
						| DbAbstr (x) ->
								let node_name = (template_name ^ (string_of_int !cur_appl_index)) in
									Hashtbl.add appl_table height node_name;
									cur_appl_index := !cur_appl_index + 1;
									let x_tree = to_tree' (height + 1) x in
										Hashtbl.remove appl_table height;
										Abstr(node_name, x_tree)
						| FreeVar (str) ->
								Var (str)
						| RefVar (x) ->
								match Hashtbl.find_opt appl_table (height - x) with
								  	| Some res -> Var (res)
										| None -> Var ("ERROR")
					in
						to_tree' 0 bt_tree
;;


(* (\. a) b *)
let do_substitution a b abstr_height =
	let rec fix_dependencies cur_height delta curB = match curB with
		| DbApplic (x, y) -> DbApplic (fix_dependencies (cur_height + 1) delta x, fix_dependencies (cur_height + 1) delta y)
		| DbAbstr (x) -> DbAbstr (fix_dependencies (cur_height + 1) delta x)
		| FreeVar (str) -> FreeVar (str)
		| RefVar (x) ->
				if x > cur_height then RefVar (x + delta - 1) else RefVar (x)
	in
		let rec do_substitution' cur_tree cur_height = match cur_tree with
			| DbApplic (x, y) -> DbApplic (do_substitution' x (cur_height + 1),
			 															 do_substitution' y (cur_height + 1))
	    | DbAbstr (x) -> DbAbstr (do_substitution' x (cur_height + 1))
			| FreeVar (str) -> FreeVar (str)
			| RefVar (x) ->
					if x == cur_height then fix_dependencies 0 (cur_height - 1) b
					else if x > cur_height then RefVar (x - 2)
					else RefVar (x)
		in
		 	do_substitution' a 1
;;

let go_to_normal_form tree =
	let rec iterate_tree height = function
		| DbApplic (DbAbstr (x), y) ->
				let res = (do_substitution x y (height + 1)) in
					(true, res)
		| DbApplic (x, y) ->
				let left_res = iterate_tree (height + 1) x in
					if (fst left_res) then (true, DbApplic (snd left_res, y))
					else begin
						let right_res = iterate_tree (height + 1) y in
							(fst right_res, DbApplic (snd left_res, snd right_res))
					end
		| DbAbstr (x) ->
				let abstr_res = iterate_tree (height + 1) x in
					(fst abstr_res, DbAbstr (snd abstr_res))
		| FreeVar (str) -> (false, FreeVar (str))
		| RefVar (x) -> (false, RefVar (x))
	in iterate_tree 0 tree
;;
