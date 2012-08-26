(* section 5.4 *)
let nextrand seed =
  let a = 16807. and m = 2147483647. in
  let t = a *. seed in
  t -. m *. floor (t /. m);;

let rec randlist n seed tail =
  if n = 0 then (seed, tail)
  else randlist (n - 1) (nextrand seed) (seed :: tail);;

let rec insert x = function
  | [] -> [x]
  | y :: rest when x < y -> x :: y :: rest
  | y :: rest -> y :: (insert x rest);;

let rec insertion_sort = function
  | [] -> []
  | x :: rest -> insert x (insertion_sort rest);;

let rec quick_sort = function
  | ([] | [_]) as l -> l
  | pivot :: rest ->
     let rec partition left right = function
       | [] -> (left, right)
       | y :: ys ->
          if y < pivot then partition (y :: left) right ys
          else partition left (y :: right) ys
     in
     let (left, right) = partition [] [] rest in
     quick_sort left @ (pivot :: quick_sort right);;


(* exercise 5.2 *)
let rec downto1 = function
  | n when n <= 1 -> [1]
  | n -> n :: downto1 (n - 1);;

let rec roman l n =
  match l with
    | [] -> ""
    | (digit, str_roman) :: rest ->
       if n >= digit then str_roman ^ roman l (n - digit)
       else roman rest n;;

let rec nested_length = function
  | [] -> 0
  | l :: rest -> List.length l + nested_length rest;;

let rec concat = function
  | [] -> []
  | l :: rest -> l @ concat rest;;

let rec zip l1 l2 =
  match (l1, l2) with
    | (([], _) | (_, [])) -> []
    | (a :: cdr1, b :: cdr2) -> (a, b) :: zip cdr1 cdr2;;

let unzip l =
  let rec separate_pair_to_list l1 l2 = function
    | [] -> (l1, l2)
    | (a, b) :: cdr -> separate_pair_to_list (l1 @ [a]) (l2 @ [b]) cdr
  in
  separate_pair_to_list [] [] l;;

let rec filter p = function
  | [] -> []
  | car :: cdr ->
     if p car then car :: filter p cdr
     else filter p cdr;;

let rec take n = function
  | [] -> []
  | car :: cdr ->
     if n > 0 then car :: take (n - 1) cdr
     else [];;

let rec drop n = function
  | [] -> []
  | car :: cdr ->
     if n > 0 then drop (n - 1) cdr
     else cdr;;

let rec max_elem = function
  | [elem] -> elem
  | car :: cdr -> max car (max_elem cdr);;


(* exercise 5.3 *)
let rec mem a = function
  | [] -> false
  | car :: cdr -> (car = a) || mem a cdr;;

let rec intersect s1 s2 =
  match s1 with
    | [] -> []
    | car :: cdr ->
       if mem car s2 then car :: intersect cdr s2
       else intersect cdr s2;;

let rec union s1 s2 =
  match s1 with
    | [] -> s2
    | car :: cdr ->
       if mem car s2 then union cdr s2
       else car :: union cdr s2;;

let rec diff s1 s2 =
  match s1 with
    | [] -> []
    | car :: cdr ->
       if mem car s2 then diff cdr s2
       else car :: diff cdr s2;;


(* exercise 5.5 *)
let rec fold_right f l e =
  match l with
    | [] -> e
    | car :: cdr -> f car (fold_right f cdr e);;

let concat l = fold_right (@) l [];;

let for_all p l =
  fold_right (fun x y -> (p x) && y) l true;;

let exists p l =
  fold_right (fun x y -> (p x) || y) l false;;


(* exercise 5.6 *)
let rec quick_sort_2 list sorted =
  match list with
    | [] -> sorted
    | [elem] -> elem :: sorted
    | pivot :: rest ->
       let rec partition left right = function
         | [] -> (left, right)
         | y :: ys ->
            if y < pivot then partition (y :: left) right ys
            else partition left (y :: right) ys
       in
       let (left, right) = partition [] [] rest in
       quick_sort_2 left (pivot :: quick_sort_2 right sorted);;


(* exercise 5.7 *)
let squares r =
  let is_int x = x = float_of_int (int_of_float x) in
  let calc_float_x y = (float_of_int r -. (float_of_int y) ** 2.) ** 0.5 in
  let y_end = (float_of_int r /. 2.) ** 0.5 in
  let rec make_pair y pairs =
    if float_of_int y >= y_end then
      pairs
    else
      let float_x = calc_float_x y in
      let pairs = if is_int float_x then (int_of_float float_x, y) :: pairs else pairs in
      make_pair (y + 1) pairs
  in make_pair 1 [];;


(* exercise 5.8 *)
let map2 f l =
  let rec rec_map rev_applied = function
    | [] -> List.rev rev_applied
    | car :: cdr -> rec_map ((f car) :: rev_applied) cdr
  in rec_map [] l;;
