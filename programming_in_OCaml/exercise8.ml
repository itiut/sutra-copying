type 'a mlist = MNil | MCons of 'a * 'a mlist ref;;

type 'a queue = {mutable head : 'a mlist; mutable tail : 'a mlist};;

let create () = {head = MNil; tail = MNil};;

let q : int queue = create ();;

let add a = function
  | {head = MNil; tail = MNil} as q ->
     let c = MCons (a, ref MNil) in
     q.head <- c; q.tail <- c
  | {tail = MCons (_, next)} as q ->
     let c = MCons (a, ref MNil) in
     next := c; q.tail <- c
  | _ -> failwith "enqueue: input queue broken";;

add 1 q; add 2 q; add 3 q;;
q;;

let peek = function
  | {head = MNil; tail = MNil} ->failwith "hd: queue is empty"
  | {head = MCons (a, _)} -> a
  | _ -> failwith "hd: queue is broen";;

peek q;;

let take = function
  | {head = MNil; tail = MNil} ->failwith "dequeue: queue is empty"
  | {head = MCons (a, next)} as q when !next = MNil ->
     q.tail <- MNil; q.head <- MNil; a
  | {head = MCons (a, next)} as q -> q.head <- !next; a
  | _ -> failwith "dequeue: queue is broen";;

take q;;
take q;;
add 4 q; take q;;


(* exercise 8.1 *)
type 'a ref = {mutable contents : 'a};;

let ref x = {contents = x};;

let (!) x = x.contents;;

let (:=) x a = x.contents <- a;;


(* exercise 8.2 *)
let incr x = x := (!x + 1);;


(* exercise 8.3 *)
let f = ref (fun y -> y + 1)
let funny_fact x = if x = 1 then 1 else x * (!f (x - 1));;


(* exercise 8.4 *)
let fib n =
  let f1 = ref 0 and f2 = ref 1 in
  for i = 1 to n do
    let temp = !f2 in
    f2 := !f2 + !f1; f1 := temp
  done;
  !f1;;


(* exrcise 8.6 *)
let fori start last body =
  let i = ref start in
  let rec fori' () =
    if !i <= last then begin
      body();
      i := !i + 1; fori' ();
    end in
  fori' ();;


(* exercise 8.7 *)
let array_iter f array =
  let rec array_iter' i =
    try f array.(i); array_iter' (i + 1) with
      | Invalid_argument "index out of bounds" -> ()
  in array_iter' 0;;


(* exercise 8.8 *)
let array_iteri f array =
  let rec array_iteri' i =
    try f (i + 1) array.(i); array_iteri' (i + 1) with
      | Invalid_argument "index out of bounds" -> ()
  in array_iteri' 0;;

array_iteri (fun i s ->
  print_string "Station #"; print_int i; print_string ": "; print_endline s)
  [|"Tokyo"; "Shinagawa"; "Shin-Yokohama"; "Nagoya"; "Kyoto"; "Shin-Osaka"|];;


(* exercise 8.10 *)
let print_int' x = output_string stdout (string_of_int x);;


(* exercise 8.11 *)
let display_file filename =
  let file = open_in filename in
  try
    let i = ref 1 in
    while true do
      print_endline (string_of_int !i ^ ": " ^ input_line file); i := !i + 1
    done;
  with End_of_file -> close_in file;;


(* exercise 8.12 *)
let cp src dst =
  let src_c = open_in src in
  let dst_c = open_out dst in
  try
    while true do
      output_string dst_c (input_line src_c ^ "\n")
    done
  with End_of_file -> close_out dst_c; close_in src_c;;
