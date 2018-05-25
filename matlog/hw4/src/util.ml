(* Parse input file *)
let (>>) x f = f x;;
let parse_str parser = (fun s -> s >> Lexing.from_string >> parser Lexer.main);;
let parse_line line = parse_str Parser.main line;;

(* Operations with table *)
let create_empty_table n =
  let htable = Hashtbl.create 200 in
    for i = 1 to n do
      Hashtbl.replace htable i (Hashtbl.create 200)
    done;
    htable
;;

let fill_table htable n default =
  for i = 1 to n do
    let cur_table = Hashtbl.find htable i in
      for j = 1 to n do
        Hashtbl.replace cur_table j default
      done
  done
;;

let set_table htable x y var = (Hashtbl.replace (Hashtbl.find htable x) y var);;
let get_table htable x y = (Hashtbl.find (Hashtbl.find htable x) y);;

let print_table htable n =
  for i = 1 to n do
    let cur_table = Hashtbl.find htable i in
      for j = 1 to n do
        if (Hashtbl.mem cur_table j) then
          Printf.printf "%d " (get_table htable i j)
      done;
      Printf.printf "\n"
  done
;;

let read_input filename =
 	let in_file = open_in filename in
    let n = List.hd (parse_line (input_line in_file)) in
      let graph = create_empty_table n in
        let rec process_string from = function
          | [] -> ()
          | x :: xs ->
            set_table graph from x from;
            process_string from xs
        in
          for i = 1 to n do
            let ends = parse_line (input_line in_file) in
              process_string i ends
          done;
          (n, graph)
;;

module IntSet = Set.Make(
  struct
    let compare = Pervasives.compare
    type t = int
  end )
