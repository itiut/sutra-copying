(* exericise 14.1 *)
let rec filter p = function
  | [] -> []
  | hd :: tl ->
     if p hd then hd :: filter p tl
     else filter p tl;;

let even li = filter (fun x -> x mod 2 = 0) li;;


(* exercise 14.3 *)
let rec fold_right f li init =
  match li with
    | [] -> init
    | hd :: tl -> f hd (fold_right f tl init);;

let concat li = fold_right (^) li "";;


(* section 14.6 *)
let rec enumerate = function
  | 0 -> []
  | n -> n :: enumerate (n - 1);;

let divisor n = List.filter (fun x -> n mod x = 0) (enumerate n);;

let perfect m =
  List.filter (fun n -> List.fold_right (+) (divisor n) 0 - n = n) (enumerate m);;


(* exercise 14.15 *)
let one_to_n n =
  List.fold_right (+) (enumerate n) 0;;


(* exercise 14.16 *)
let fac n =
  List.fold_right ( * ) (enumerate n) 1;;
