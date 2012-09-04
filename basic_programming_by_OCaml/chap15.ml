(* exercise 15.2 *)
let rec gcd m n =
  match (m, n) with
    | (m, 0) -> m
    | (m, n) -> gcd n (m mod n);;


(* exercise 15.3 *)
let rec intlist_i_to_n i n =
  if i > n then []
  else i :: intlist_i_to_n (i + 1) n;;

let rec sieve = function
  | [] -> []
  | hd :: tl ->
     hd :: sieve (List.filter (fun x -> x mod hd <> 0) tl);;

let prime n =
  sieve (intlist_i_to_n 2 n);;
