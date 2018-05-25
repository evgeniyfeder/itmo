open Data;;
open Printf;;
open Check;;

let (-->) a b = Binop (Impl, a, b);;

let transform_step assump_list assump_size line_list annotation cur a = match annotation with
| Axiom i ->
  [cur --> (a --> cur);
   cur;
   a --> cur]
| Assumption i ->
  let cur_as = (List.nth assump_list (i - 1)) in
    if assump_size == i then
      [a --> (a --> a);
       (a --> (a --> a)) --> ((a --> ((a --> a) --> a)) --> (a --> a));
       a --> ((a --> a) --> a);
       (a --> ((a --> a) --> a)) --> (a --> a);
       (a --> a)]
    else
    [cur_as --> (a --> cur_as);
     cur_as;
     a --> cur_as]
| ModusPonus (i, k) ->
  let m_i = cur in
    let m_j = (Hashtbl.find line_list (snd (Hashtbl.find proofed_table cur))) in
      [(a --> m_j) --> ((a --> (m_j --> m_i)) --> (a --> m_i));
       (a --> (m_j --> m_i)) --> (a --> m_i);
       (a --> m_i)]
| _ -> []
;;

let deduct assump_list expr_list a =
  let line_list = Hashtbl.create 1024 in
    let assump_size = (List.length assump_list) in
      let res = ref [] in
        let rec deduct' expr_list ind = match expr_list with
        | [] -> ()
        | x :: xs ->
            let annotation = do_one_step x ind in
              res := !res @ (transform_step assump_list assump_size line_list annotation x a);
              Hashtbl.add line_list ind x;
              deduct' xs (ind + 1)
        in
        fill_assumptions assump_list 1;
        deduct' expr_list 1;
        Hashtbl.clear assumptions_table;
        Hashtbl.clear proofed_table;
        Hashtbl.clear mp_parts;
        Hashtbl.clear expressions_table;
        !res
;;
