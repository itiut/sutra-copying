(* section 7.1 *)
let rec nth n l =
  match (n, l) with
    | (n, _) when n <= 0 -> None
    | (1, a :: _) -> Some a
    | (_, _ :: cdr) -> nth (n - 1) cdr
    | (_, []) -> None;;

let rec find x = function
  | [] -> None
  | a :: l when a = x -> Some 1
  | _ :: l ->
     match find x l with
       | None -> None
       | Some i -> Some (i + 1);;

let map_sqrt l =
  List.map (fun x -> if x < 0.0 then None else Some (sqrt x)) l;;


(* section 7.2 *)
let rec fact n =
  if n < 0 then raise (Invalid_argument "fact: negative argument")
  else if n = 0 then 1 else n * fact (n - 1);;

let rec find' x = function
  | [] -> raise Not_found
  | car :: cdr when car = x -> 1
  | _ :: cdr -> 1 + find' x cdr;;

let find x l = try find' x l with Not_found -> 0;;

let map_sqrt l =
  let sqrt' x =
    if x < 0.0 then raise (Invalid_argument "sqrt'")
    else sqrt x in
  try Some (List.map sqrt' l) with Invalid_argument "sqrt'" -> None;;


(* exercise 7.1 *)
let find x l =
  let rec find' i = function
    | [] -> raise Not_found
    | car :: cdr ->
       if car = x then Some i else find' (i + 1) cdr
  in try find' 1 l with Not_found -> None;;


(* exercise 7.2 *)
let prod_list l =
  let rec prod_list' prod = function
    | [] -> prod
    | car :: cdr ->
       if car = 0 then failwith "find zero"
       else prod_list' (prod * car) cdr
  in try prod_list' 1 l with Failure "find zero" -> 0;;


(* exercise 7.3 *)
let rec change coins amount =
  match (coins, amount) with
    | (_, 0) -> []
    | ((c :: rest) as coins, total) ->
       if c > total then change rest total
       else
         (try c:: change coins (total - c) with
             Failure "change" -> change rest total)
    | _ -> failwith "change";;
