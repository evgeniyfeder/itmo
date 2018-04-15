open Data;;

(* Shortcut for calling parser *)
let (>>) x f = f x;;

let parse_str parser = (fun s -> s >> Lexing.from_string >> parser Lexer.main);;
let parse_head head = parse_str Parser.head head;;
let parse_expr = parse_str Parser.main;;

(**** Checking hash tables ****)
let assumptions_table = Hashtbl.create 1024;; (* tree -> int *)
let proofed_table = Hashtbl.create 1024;;		  (* tree -> (int, int) *)
let mp_parts = Hashtbl.create 1024 ;;				  (* tree -> list:[(tree, int)] *)
let expressions_table = Hashtbl.create 1024;; (* tree -> int *)

let rec fill_assumptions data ind =
  match data with
	| [] -> ()
	| x :: xs ->
		Hashtbl.add assumptions_table x ind;
		fill_assumptions xs (ind + 1)

let find_opt htable statement = if Hashtbl.mem htable statement then Some (Hashtbl.find htable statement) else None;;
let check_assumption statement = find_opt assumptions_table statement;;
let check_mp statement = find_opt proofed_table statement;;

let check_axioms statement = match statement with
  | Binop(Impl, a1, Binop(Impl, b1, a2))
  when(a1 = a2) -> Some (1)
  | Binop(Impl, Binop(Impl, a1, b1), Binop(Impl, Binop(Impl, a2, Binop(Impl, b2, c1)), Binop(Impl, a3, c2)))
  when(a1 = a2 && a2 = a3 && b1 = b2 && c1 = c2) -> Some (2)
  | Binop(Impl, a1, Binop(Impl, b1, Binop(Conj, a2, b2)))
  when(a1 = a2 && b1 = b2) -> Some (3)
  | Binop(Impl, Binop(Conj, a1, b1), a2)
  when(a1 = a2) -> Some (4)
  | Binop(Impl, Binop(Conj, a1, b1), b2)
  when(b1 = b2) -> Some (5)
  | Binop(Impl, a1, Binop(Disj, a2, b1))
  when(a1 = a2) -> Some (6)
  | Binop(Impl, b1, Binop(Disj, a1, b2))
  when(b1 = b2) -> Some (7)
  | Binop(Impl, Binop(Impl, a1, c1), Binop(Impl, Binop(Impl, b1, c2), Binop(Impl, Binop(Disj, a2, b2), c3)))
  when(a1 = a2 && b1 = b2 && c1 = c2 && c2 = c3) -> Some (8)
  | Binop(Impl, Binop(Impl, a1, b1), Binop(Impl, Binop(Impl, a2, Neg(b2)), Neg(a3)))
  when(a1 = a2 && a2 = a3 && b1 = b2) -> Some (9)
  | Binop(Impl, Neg(Neg(a1)), a2)
  when(a1 = a2) -> Some (10)
  | _-> None
;;

(* Working with bad cases functions *)
let add_mp_case statement ind =
	match statement with
	| Binop (Impl, a, b) ->
		if (Hashtbl.mem expressions_table a)
			then Hashtbl.replace proofed_table b (ind, (Hashtbl.find expressions_table a))
		else if (Hashtbl.mem mp_parts a)
			then Hashtbl.replace mp_parts a ((b, ind) :: (Hashtbl.find mp_parts a))
		else Hashtbl.add mp_parts a [(b, ind)]
	| _ -> ()
;;


let update_old_mp statement ind =
	if (Hashtbl.mem mp_parts statement) then begin
		List.iter (fun (e, i) -> Hashtbl.replace proofed_table e (i, ind)) (Hashtbl.find mp_parts statement);
		Hashtbl.replace mp_parts statement [];
	end
;;


let get_annotation s =
	match (check_assumption s) with
	| Some (i) -> Assumption (i)
	| _ -> match (check_axioms s) with
		| Some (i) -> Axiom (i)
		| _ -> match (check_mp s) with
			| Some(a, b) -> ModusPonus (a, b)
			| _ -> Incorrect
;;

(* Add one string to proof *)
let do_one_step statement ind = begin
	let res = get_annotation statement in
	add_mp_case statement ind;
	update_old_mp statement ind;
	Hashtbl.replace expressions_table statement ind;
	res
end;;
