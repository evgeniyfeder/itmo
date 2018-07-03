open Data;;
open Buffer;;
open Printf;;
open Deduct;;

let (ic,oc) = (open_in "input.txt", open_out "output.txt");;

(*** Utilities ***)
(* Parser function *)
let (>>) x f = f x;;

let parse_str parser = (fun s -> s >> Lexing.from_string >> parser Lexer.main);;
let parse_head head = parse_str Parser.head head;;
let parse_expr expr = parse_str Parser.main expr;;
let parse_lemma a b = (fun s -> s >> Lexing.from_string >> Parser.main (Lexer.lemma a b))

let get_lemma file_name a b =
	List.map (parse_lemma a b) (read_file ("proofs/" ^ file_name ^ ".txt"))
;;

(* Shortcut for calling parser *)
let error = ref [];;
let fixed_args = Hashtbl.create 10;;

let rec get_proof = function
  | Var a ->
    (let value = Hashtbl.find fixed_args a in
      (match value with
        | Neg a -> (false, [value])
        | _ -> (true, [value])))
  | Neg a ->
    (let (is_true, proof) = get_proof a in
      (not is_true, proof @ (get_lemma ("not_" ^ (string_of_bool is_true)) a (Var ""))))
  | Binop (op, a, b) ->
    let (is_true_1, proof_1) = get_proof a in
      let (is_true_2, proof_2) = get_proof b in
        ((apply_op op) is_true_1 is_true_2,
              proof_1 @ proof_2 @ (get_lemma (get_file_name_by_op is_true_1 is_true_2 op) a b))
;;

let rec prove expr assump args = match args with
  | [] ->
    let (true_flag, proof)  = get_proof expr in
      if (not true_flag) then error := assump;
      (true_flag, proof)
  | x :: xs ->
    let pos_var = Var (x) in
      let neg_var = Neg (Var(x)) in
        let pos_assump = assump @ [pos_var] in
          let neg_assump = assump @ [neg_var] in
            Hashtbl.replace fixed_args x pos_var;
            let (check_flag_1, prove_text_1) = prove expr pos_assump xs in
              Hashtbl.replace fixed_args x neg_var;
              let (check_flag_2, prove_text_2) = prove expr neg_assump xs in
                if (not check_flag_1 || not check_flag_2) then (false, [])
                else begin
                  let deducted_1 = deduct pos_assump prove_text_1 pos_var in
                    let deducted_2 = deduct neg_assump prove_text_2 neg_var in
                      let merge = get_lemma "lemma_merge" expr pos_var in
                        (true, deducted_1 @ deducted_2 @ merge)
                end
;;

let rec check_general_with_fixed = function
  | Var a ->
    (let value = Hashtbl.find fixed_args a in
      (match value with
        | Neg a -> false
        | _ -> true))
	| Neg a ->
  	(let is_true = check_general_with_fixed a in
      not is_true)
  | Binop (op, a, b) ->
    let is_true_1 = check_general_with_fixed a in
      let is_true_2 = check_general_with_fixed b in
        (apply_op op) is_true_1 is_true_2
;;

let rec check_general expr assump args = match args with
  | [] ->
    let true_flag = check_general_with_fixed expr in
      if (not true_flag) then error := assump;
      true_flag
  | x :: xs ->
    let pos_var = Var (x) in
      let neg_var = Neg (Var(x)) in
        let pos_assump = assump @ [pos_var] in
          let neg_assump = assump @ [neg_var] in
            Hashtbl.replace fixed_args x pos_var;
            let check_flag_1 = check_general expr pos_assump xs in
              Hashtbl.replace fixed_args x neg_var;
              let check_flag_2 = check_general expr neg_assump xs in
                not (not check_flag_1 || not check_flag_2)
;;

let print_error_arguments oc arg_list =
  let rec print_error_arguments' = function
      | x :: [] -> (match x with
        | Neg (Var var) -> var ^ "=Л"
        | Var var       -> var ^ "=И"
        | _ -> "")
      | x :: xs -> (match x with
        | Neg (Var var) -> var ^ "=Л, " ^ (print_error_arguments' xs)
        | Var var       -> var ^ "=И, " ^ (print_error_arguments' xs)
        | _ -> "")
      | [] -> ""
  in
  fprintf oc "%s\n" ("Высказывание ложно при " ^ (print_error_arguments' arg_list))
;;


let rec dededuct oc assump e =
    match assump with
    | [] -> ()
    | x :: xs -> (match e with
                | Binop (Impl, a, b) ->
                  fprintf oc "%s\n%s\n" (tree_to_string a) (tree_to_string b);
                  dededuct oc xs b
                | _ -> ())

(* Working parts *)
let line = (input_line ic);;

let input = parse_head line;;
let assumptions = fst input;;
let input_expr = snd input;;

let need_prove = shift_to_right assumptions input_expr
let variables_set = get_variables need_prove;;
print_endline ;;

let check_truth_flag = check_general need_prove [] (SS.elements variables_set);;
if (not check_truth_flag) then
  print_error_arguments oc !error
else begin
	let (res_truth, res_proof) = prove need_prove [] (SS.elements variables_set) in
	  print_tree_list oc assumptions;
	  fprintf oc "|-";
	  fprintf oc "%s\n" (tree_to_string input_expr);
	  List.iter (fun x -> (fprintf oc "%s\n" (tree_to_string x))) res_proof;
	  dededuct oc assumptions need_prove
end;;
close_out oc;;
close_in ic;;
