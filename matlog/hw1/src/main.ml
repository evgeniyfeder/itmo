open Data;;
open Buffer;;
open Printf;;
open Check;;

let (ic,oc) = (open_in "input.txt", open_out "output.txt");;
fill_assumptions (parse_head (input_line ic)) 1;;
let ind = ref 1;;

try
  while true do
    let line = input_line ic in
    if (line <> "") then begin
      let annotation = do_one_step (parse_expr line) !ind in
      fprintf oc "(%d) %s %s\n" !ind line (annotation_to_string annotation);
			ind := !ind + 1;
    end;
  done;
with
  End_of_file -> close_out oc; close_in ic;
;;
