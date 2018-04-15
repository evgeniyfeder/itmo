open Data;;
open Buffer;;
open Printf;;
open Check;;

let (ic,oc) = (open_in "input.txt", open_out "output.txt");;


let process_assump assump_parts oc =
  let assump_left = (fst assump_parts) in
    let assump_right = (snd assump_parts) in
      fill_assumptions assump_left 1;
      let rev_left = (List.rev assump_left) in
        let res_left = List.rev (List.tl rev_left) in
          if ((List.length res_left) > 0) then begin
            fprintf oc "%s" (tree_to_string (List.hd res_left));
            if ((List.length res_left) > 1) then (print_tree_list oc (List.tl res_left));
          end;
          fprintf oc "|-(%s)->(%s)\n" (tree_to_string (List.hd (List.rev assump_left))) (tree_to_string assump_right);
          (List.hd rev_left)
;;

let assump_parts = parse_head (input_line ic);;
let assump_list = (fst assump_parts);;
let assump_size = List.length assump_list;;
let a = process_assump assump_parts oc;;
let a_str = tree_to_string a;;
let ind = ref 1;;

let line_list = Hashtbl.create 1024;;

let transform_step oc annotation cur a_str = match annotation with
| Axiom i ->
  let cur_str = (tree_to_string cur) in
    fprintf oc "(%s)->(%s)->(%s)\n(%s)\n(%s)->(%s)\n" cur_str a_str cur_str cur_str a_str cur_str
| Assumption i ->
  let cur_as = (tree_to_string (List.nth assump_list (i - 1))) in
    if assump_size == i then
      fprintf oc "(%s)->((%s)->(%s))\n((%s)->((%s)->(%s)))->((%s)->((%s)->(%s))->(%s))->((%s)->(%s))\n(%s)->(((%s)->(%s))->(%s))\n((%s)->((%s)->(%s))->(%s))->((%s)->(%s))\n((%s)->(%s))\n"
                  a_str a_str a_str
                  a_str a_str a_str a_str a_str a_str a_str a_str a_str
                  a_str a_str a_str a_str
                  a_str a_str a_str a_str a_str a_str
                  a_str a_str
    else
      fprintf oc "(%s)->(%s)->(%s)\n(%s)\n(%s)->(%s)\n"
                  cur_as a_str cur_as
                  cur_as
                  a_str cur_as
| ModusPonus (i, k) ->
  let m_i = (tree_to_string cur) in
    let m_j = (tree_to_string (Hashtbl.find line_list (snd (Hashtbl.find proofed_table cur)))) in
      fprintf oc "((%s)->(%s))->((%s)->(%s)->(%s))->((%s)->(%s))\n((%s)->(%s)->(%s))->((%s)->(%s))\n((%s)->(%s))\n"
                  a_str m_j a_str m_j m_i a_str m_i
                  a_str m_j m_i a_str m_i
                  a_str m_i
| _ -> ()
;;

try
  while true do
    let line = input_line ic in begin
      if (line <> "") then
        let cur_tree = parse_expr line in
          let annotation = do_one_step cur_tree !ind in
            transform_step oc annotation cur_tree a_str;
            Hashtbl.add line_list !ind cur_tree;
    			  ind := !ind + 1;
      end
  done;
with
  End_of_file -> close_out oc; close_in ic;
;;
