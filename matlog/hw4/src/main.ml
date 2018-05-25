open Util;;

let oc = open_out "output.txt";;

let (n, graph) = read_input "input.txt";;

type relation = Fail | Less | More | Eq;;

let relation_to_string = function
	| Fail -> "Fail"
	| Less -> "Less"
	| More -> "More"
  | Eq   -> "Eq"
;;

let compare_table = create_empty_table n;;
fill_table compare_table n Fail;;

let update_compare_table a b =
  let cur_map = Hashtbl.find compare_table a in
    match Hashtbl.find cur_map b with
    | Fail ->
      set_table compare_table a b Less;
      set_table compare_table b a More
    | More ->
      set_table compare_table a b Eq;
      set_table compare_table b a Eq
    | _ -> ()

let used = Hashtbl.create 200;;
let rec dfs' cur =
  if (not (Hashtbl.mem used cur)) then begin
    Hashtbl.replace used cur (IntSet.singleton cur);
    let cur_set = ref (IntSet.singleton cur) in
      Hashtbl.iter (fun key value -> cur_set := IntSet.union !cur_set (dfs' key)) (Hashtbl.find graph cur);
      IntSet.iter (fun s -> update_compare_table cur s) !cur_set;
      update_compare_table cur cur;
      Hashtbl.replace used cur !cur_set;
      !cur_set
  end else Hashtbl.find used cur
;;

for i = 1 to n do
  dfs' i
done;;

for i = 1 to n do
  let cur_table = Hashtbl.find compare_table i in
    for j = 1 to n do
      if (Hashtbl.mem cur_table j) then
        Printf.printf "%s " (relation_to_string (get_table compare_table i j))
    done;
    Printf.printf "\n"
done

let compare a b = get_table compare_table a b;;

let leq a b = (compare a b == More || compare a b == Eq);;
let req a b = (compare a b == Less || compare a b == Eq);;

let do_operation condidates_checker minimum_checker a b =
    let condidates = ref  [] in
      for c = 1 to n do
        if (condidates_checker a b c) then condidates := c :: !condidates
      done;
      if ((List.length (!condidates)) == 0) then -1
      else begin
        let cur_min = ref (List.hd (!condidates)) in
          List.iter (fun cur -> if  (minimum_checker cur !cur_min) then cur_min := cur) !condidates;
          let result = ref !cur_min in
            List.iter (fun cur -> if not (minimum_checker !cur_min cur) then result := -1) !condidates;
            !result
      end

let get_plus_error a b = "Операция '+' не определена: " ^ (string_of_int a) ^ "+" ^ (string_of_int b);;
let (+.) = do_operation (fun a b c -> (leq c b) && (leq c a)) req;;

let get_mul_error a b = "Операция '*' не определена: " ^ (string_of_int a) ^ "*" ^ (string_of_int b);;
let ( *. ) = do_operation (fun a b c -> (req c b) && (req c a)) leq;;

let get_impl_error a b = "Операция '->' не определена: " ^ (string_of_int a) ^ "->" ^ (string_of_int b);;
let (-->) = do_operation (fun a b c -> req (a *. c) b) leq;;

let check_operation op error_handler =
  let result = ref true in
    for a = 1 to n do
      for b = 1 to n do
        let res = (op a b) in
          if !result && (res == -1) then begin
            Printf.fprintf oc "%s\n" (error_handler a b);
            result := false
          end

      done
    done;
    !result
;;

let get_distr_error a b c = "Нарушается дистрибутивность: " ^ (string_of_int a) ^ "*(" ^ (string_of_int b) ^ "+" ^ (string_of_int c) ^ ")";;

let check_destribution a =
  let result = ref true in
    for a = 1 to n do
      for b = 1 to n do
        for c = 1 to n do
          if !result && (a *. (b +. c) <> a *. b +. a *. c) then begin
            Printf.fprintf oc "%s\n" (get_distr_error a b c);
            result := false
          end
        done
      done
    done;
    !result
;;

let check_bulean a =
  let result = ref true in
    let zero = do_operation (fun a b c -> true) req 1 1 in
      let one = do_operation (fun a b c -> true) leq 1 1 in
        for a = 1 to n do
          if !result && (a +. (a --> zero)) <> one then begin
            Printf.fprintf oc "Не булева алгебра: %d+~%d" a a;
            result := false
          end
        done;
        !result
;;

if check_operation (+.) get_plus_error then
  if check_operation ( *. ) get_mul_error then
    if check_destribution () then
      if check_operation (-->) get_impl_error then
        if check_bulean () then
          Printf.fprintf oc "Булева алгебра\n"
