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

type algo_term =
	| Impl of algo_term * algo_term
	| TypeVar of int
;;

let rec aterm_to_string = function
	| Impl (x, y) -> "(" ^ (aterm_to_string x) ^ " -> " ^ (aterm_to_string y) ^ ")"
	| TypeVar (x) -> "t" ^ (string_of_int x)
;;

type equality = { left : algo_term; right : algo_term };;

let equality_to_string equality = (aterm_to_string equality.left) ^ " = " ^ (aterm_to_string equality.right);;

let rec eq_system_to_string = function
	| [] -> ""
	| x :: xs -> (equality_to_string x) ^ "\n" ^ (eq_system_to_string xs)
;;

let get_eq_system tree =
	let var_to_algo_type = Hashtbl.create 1024 in
		let next_var_num = ref 1 in
			let rec get_eq_system' tree = match tree with
				| Var (x) -> begin
						match Hashtbl.find_opt var_to_algo_type x with
							| Some (y) -> ([], TypeVar(y))
							| None ->
									next_var_num := !next_var_num + 1;
									Hashtbl.add var_to_algo_type x (!next_var_num - 1);
									([], TypeVar(!next_var_num - 1))
						end
				| Abstr (var, x) ->
						let var_type = !next_var_num in
							next_var_num := !next_var_num + 1;
							Hashtbl.add var_to_algo_type var var_type;
							let (x_res_left, x_res_right) = get_eq_system' x in
									Hashtbl.remove var_to_algo_type var;
									(x_res_left, Impl (TypeVar(var_type), x_res_right))
				| Applic (x, y) ->
						let (x_eq_system, x_type) = get_eq_system' x in
							let (y_eq_system, y_type) = get_eq_system' y in
								next_var_num := !next_var_num + 1;
								(({left=x_type; right=Impl(y_type, TypeVar(!next_var_num - 1))} :: x_eq_system) @ y_eq_system, TypeVar(!next_var_num - 1))
			in
				(var_to_algo_type, get_eq_system' tree)
;;

exception UniFail of string

let unification eq_system =
	let subst_list = ref [] in
		(* Substitution *)
		let rec do_subst_eq elem subst = match elem with
			| Impl(x, y) -> Impl(do_subst_eq x subst, do_subst_eq y subst)
			| TypeVar (x) -> match subst.left with TypeVar(l) -> if l == x then subst.right else elem
		in

		let rec do_subst eq_system subst = match eq_system with
			| [] -> []
			| x :: xs -> {left=(do_subst_eq x.left subst); right=(do_subst_eq x.right subst)} :: (do_subst xs subst)
		in


		(* One unififcation step *)
		let rec unification_step = function
		 	| [] -> []
			| x :: xs -> match x with
					| {left = l; right = r} when l = r -> unification_step xs
					| {left = TypeVar(l); right = r} ->
							subst_list := x :: !subst_list;
							xs
					| {left = l; right = TypeVar(r)} -> {left = TypeVar(r); right = l} :: xs
					| {left = Impl(x, y); right = Impl(t, h)} -> ({left = x; right = t} :: ({left = y; right = h} :: xs))
		in

		(* Consistency *)
		let rec check_non_consistency_eq left_name = function
			| Impl (x, y) -> (check_non_consistency_eq left_name x) || (check_non_consistency_eq left_name y)
			| TypeVar (x) -> left_name == x
		in

		let rec check_non_consistency equality = match equality with
			| {left=TypeVar(x); right=r} -> (check_non_consistency_eq x r)
			| _ -> false
		in
			let step_list_ref = ref eq_system in
				while ((List.length !step_list_ref) != 0) do
					let old_size = List.length !subst_list in
						(* printf "%s\n////\n" (eq_system_to_string !step_list_ref); *)
						step_list_ref := unification_step !step_list_ref;
						if old_size != (List.length !subst_list) then
							let is_non_consistency = check_non_consistency (List.hd !subst_list) in begin
								if is_non_consistency
								then raise (UniFail "Expression has no type")
								else step_list_ref := do_subst !step_list_ref (List.hd !subst_list)
							end
				done;
				!subst_list
;;

let get_hashtbl_eq_system eq_system =
	let res = Hashtbl.create 1024 in
	 	let rec get_hashtbl_eq_system' = function
			| [] -> ()
			| x :: xs -> begin match x.left with | TypeVar (n) -> Hashtbl.add res n x.right end; get_hashtbl_eq_system' xs
		in
			get_hashtbl_eq_system' eq_system;
			res
;;

let rec subst_eq_system type_schema eq_system = match type_schema with
	| Impl (x, y) -> Impl(subst_eq_system x eq_system, subst_eq_system y eq_system)
	| TypeVar (x) -> match Hashtbl.find_opt eq_system x with
			| Some (res) -> subst_eq_system res eq_system
			| None -> TypeVar (x)

;;

let rec print_level height = match height with
	| 0 -> ""
	| _ -> "*   " ^ print_level (height - 1)
;;

module SS = Set.Make(String);;

let rec print_context eq_system map_context = function
	| x :: [] -> x ^ " : " ^ (aterm_to_string (subst_eq_system (TypeVar(Hashtbl.find map_context x)) eq_system)) ^ " "
	| x :: xs -> x ^ " : " ^ (aterm_to_string (subst_eq_system (TypeVar(Hashtbl.find map_context x)) eq_system)) ^ ", " ^ (print_context eq_system map_context xs)
	| _ -> ""
;;

let generate_string height map_context name right_type rule_nun eq_system =
		let s = ref SS.empty in
			Hashtbl.iter (fun key value -> s := SS.add key !s) map_context;
			print_level height ^ (print_context eq_system map_context (SS.elements !s)) ^ "|- " ^ name ^ " : " ^ (aterm_to_string right_type) ^ " [rule #" ^ (string_of_int rule_nun) ^ "]\n"
;;

let generate_deduction_tree tree eq_system map_free =
	let free_vars_inited = ref SS.empty in
	let var_to_algo_type = Hashtbl.create 1024 in
		Hashtbl.iter (fun key value -> Hashtbl.add var_to_algo_type key value) map_free;
		let next_var_num = ref 1 in
			(* (height, tree) -> (context_set, name, type, string_tree) *)
			let rec generate_deduction_tree' height tree = match tree with
				| Var (x) -> begin
						match Hashtbl.find_opt var_to_algo_type x with
							| Some (y) ->
									if ((Hashtbl.mem map_free x) && not (SS.mem x !free_vars_inited)) then begin
										next_var_num := !next_var_num + 1;
										free_vars_inited := SS.add x !free_vars_inited;
										let z = !next_var_num - 1 in
											(x, TypeVar(z), generate_string height var_to_algo_type x (subst_eq_system (TypeVar(z)) eq_system) 1 eq_system)
									end else begin
										(x, TypeVar(y), (generate_string height var_to_algo_type x (subst_eq_system (TypeVar(y)) eq_system) 1 eq_system))
									end
							| None ->
									next_var_num := !next_var_num + 1;
									let y = !next_var_num - 1 in
										(x, TypeVar(y), generate_string height var_to_algo_type x (subst_eq_system (TypeVar(y)) eq_system) 1 eq_system)
						end
				| Abstr (var, x) ->
						let var_type = !next_var_num in
							next_var_num := !next_var_num + 1;
							Hashtbl.add var_to_algo_type var var_type;
							let (x_name, x_type, x_string) = generate_deduction_tree' (height + 1) x in
									Hashtbl.remove var_to_algo_type var;
									let new_type = subst_eq_system (Impl (TypeVar(var_type), x_type)) eq_system in
									let new_name = ("(\\" ^ var ^ "." ^ x_name ^ ")") in
										(new_name, new_type,
											(generate_string height var_to_algo_type new_name new_type 3 eq_system) ^ x_string)
				| Applic (x, y) ->
						let (x_name, x_type, x_string) = generate_deduction_tree' (height + 1) x in
							let (y_name, y_type, y_string) = generate_deduction_tree' (height + 1) y in
								next_var_num := !next_var_num + 1;
								let new_type = subst_eq_system (TypeVar(!next_var_num - 1)) eq_system in
								let new_name = "(" ^ x_name ^ " " ^ y_name ^ ")" in
								(new_name, new_type,
									(generate_string height var_to_algo_type new_name new_type 2 eq_system) ^ x_string ^ y_string)
			in
				let (t_name, t_type, t_string) = generate_deduction_tree' 0 tree in
					t_string
;;
