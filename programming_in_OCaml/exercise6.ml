(* section 6.1 *)
type student = {name : string; id : int};;


(* section 6.2 *)
type figure =
  | Point
  | Circle of int
  | Rectangle of int * int
  | Square of int;;

let figs = [Point; Square 5; Rectangle (4, 9); Circle 3];;

let area_of_figure = function
  | Point -> 0
  | Circle r -> r * r * 3
  | Rectangle (x, y) -> x * y
  | Square x -> x * x;;

List.map area_of_figure figs;;

let similar x y =
  match (x, y) with
    | (Point, Point) | (Circle _, Circle _) | (Square _, Square _) -> true
    | (Rectangle (l1, l2), Rectangle (l3, l4)) -> l1 * l4 = l2 * l3
    | (Rectangle (l1, l2), Square _) -> l1 = l2
    | (Square _, Rectangle (l1, l2)) -> l1 = l2
    | _ -> false;;

similar (Rectangle (2, 4)) (Rectangle (1, 2));;


(* section 6.3 *)
type color = Black | Blue | Red | Magenta | Green | Cyan | Yellow | White;;

let reverse_color = function
  | Black   -> White
  | Blue    -> Yellow
  | Red     -> Cyan
  | Magenta -> Green
  | Green   -> Magenta
  | Cyan    -> Red
  | Yellow  -> Blue
  | White   -> Black;;


type nat = Zero | OneMoreThan of nat;;

let zero = Zero;;
let one = OneMoreThan Zero;;
let two = OneMoreThan (OneMoreThan Zero);;

let rec add m n =
  match m with
    | Zero -> n
    | OneMoreThan m' -> OneMoreThan (add m' n);;


type intlist = INil | ICons of int * intlist;;


type even = Zero | OMT_E of odd
and odd = OMT_O of even;;

let rec o_plus_e (OMT_O e1) e2 =
  OMT_O (e_plus_e e1 e2)
and e_plus_e e1 e2 =
  match e1 with
    | Zero -> e2
    | OMT_E o -> OMT_E (o_plus_e o e2);;


type 'a mylist = Nil | Cons of 'a * 'a mylist;;

type 'a with_location = {loc_x: float; loc_y: float; body: 'a};;

{loc_x = 0.; loc_y = 0.; body = Point};;

type ('a, 'b) list_with_tail =
    Nil of 'b | Cons of 'a * ('a, 'b) list_with_tail;;

Cons (2, Cons (3, Nil ("end")));;

let fact n =
  let rec fact' = function
    | 0 -> 1
    | n -> n * fact' (n - 1)
  in
  if n < 0 then None else Some (fact' n);;


(* section 6.4 *)
type 'a tree = Lf | Br of 'a * 'a tree * 'a tree;;

let chartree = Br ('a', Br ('b', Br ('d', Lf, Lf), Lf),
                   Br ('c', Br ('e', Lf, Lf), Br ('f', Lf, Lf)));;

let rec size = function
  | Lf -> 0
  | Br (_, left, right) -> 1 + size left + size right;;

let rec depth = function
  | Lf -> 0
  | Br (_, left, right) -> 1 + max (depth left) (depth right);;

let comptree = Br (1, Br (2, Br (4, Lf, Lf),
                          Br (5, Lf, Lf)),
                   Br (3, Br (6, Lf, Lf),
                       Br (7, Lf, Lf)));;

let rec preorder = function
  | Lf -> []
  | Br (x, left, right) ->
     x :: (preorder left) @ (preorder right);;

let rec inorder = function
  | Lf -> []
  | Br (x, left, right) ->
     (inorder left) @ (x :: inorder right);;

let rec postorder = function
  | Lf -> []
  | Br (x, left, right) ->
     (postorder left) @ (postorder right) @ [x];;

let rec preord t l =
  match t with
    | Lf -> l
    | Br (x, left, right) ->
       x :: (preord left (preord right l));;

let rec mem t x =
  match t with
    | Lf -> false
    | Br (y, left, right) ->
       if x = y then true
       else if x < y then mem left x
       else mem right x;;

let rec add t x =
  match t with
    | Lf -> Br (x, Lf, Lf)
    | (Br (y, left, right) as whole) when x = y -> whole
    | Br (y, left, right) when x < y -> Br (y, add left x, right)
    | Br (y, left, right) -> Br (y, left, add right x);;

type 'a rosetree = RLf | RBr of 'a * 'a rosetree list;;

type 'a option = None | Some of 'a;;

type ('a, 'b) xml = XLf of 'b opiton | XBr of 'a * ('a, 'b) xml list;;

let rec rosetree_of_tree = function
  | Lf -> RLf
  | Br (a, left, right) -> RBr (a, List.map rosetree_of_tree [left; right]);;

let rec tree_of_rtree = function
  | RLf -> Br (None, Lf, Lf)
  | RBr (a, rtrees) -> Br (Some a, tree_of_rtreelist rtrees, Lf)
and tree_of_rtreelist = function
  | [] -> Lf
  | rtree :: rest -> let Br (a, left, Lf) = tree_of_rtree rtree in
                     Br (a, left, tree_of_rtreelist rest);;

let rtree =
  RBr ("a", [
    RBr ("b", [
      RBr ("c", [RLf]);
      RLf;
      RBr ("d", [RLf])]);
    RBr ("e", [RLf]);
    RBr ("f", [RLf])]);;

tree_of_rtree rtree;;


(* section 6.5 *)
type intseq = Cons of int * (int -> intseq);;

let rec f x = Cons (x + 1, f);;

let rec step2 x = Cons (x + 2, step2);;

let Cons (x1, f1) = step2 0;;
let Cons (x2, f2) = f1 x1;;
let Cons (x3, f3) = f2 x2;;

let rec step n x = Cons (x + n, step (n + 1));;

let Cons (x1, f1) = step 1 0;;
let Cons (x2, f2) = f1 x1;;
let Cons (x3, f3) = f2 x2;;
let Cons (x4, f4) = f3 x3;;
let Cons (x5, f5) = f4 x4;;

let rec nthseq n (Cons (x, f)) =
  if n = 1 then x
  else nthseq (n - 1) (f x);;


let is_prime x =
  let rec is_divisible_from_2_to n =
    (n > 1) && ((x mod n = 0) || is_divisible_from_2_to (n - 1))
  in not (is_divisible_from_2_to (x - 1));;

let rec next_prime x =
  if is_prime (x + 1) then x + 1 else next_prime (x + 1);;

let rec prime_seq x =
  if is_prime (x + 1) then Cons (x + 1, prime_seq) else prime_seq (x + 1);;

nthseq 20 (prime_seq 1);;


(* exercise 6.1 *)
type figure =
  | Point
  | Circle of int
  | Rectangle of int * int
  | Square of int;;

let similar x y =
  match (x, y) with
    | (Point, Point) | (Circle _, Circle _) | (Square _, Square _) -> true
    | (Rectangle (l1, l2), Rectangle (l3, l4)) -> l1 * l4 = l2 * l3
    | (Rectangle (l1, l2), Square _) | (Square _, Rectangle (l1, l2)) -> l1 = l2
    | _ -> false;;


(* exercise 6.2 *)
type 'a with_location = {loc_x: float; loc_y: float; body: 'a};;

let overlap {loc_x = x1; loc_y = y1; body = body1} {loc_x = x2; loc_y = y2; body = body2} =
  match (body1, body2) with
    | (Point, Point) -> x1 = x2 && y1 = y2
    | (Point, Circle r) | (Circle r, Point) ->
       (x1 -. x2) ** 2. +. (y1 -. y2) ** 2. <= float_of_int r ** 2.
    | (Point, Rectangle (w, h)) ->
       let half_w = float_of_int w /. 2. in
       let half_h = float_of_int h /. 2. in
       x2 -. half_w <= x1 && x1 <= x2 +. half_w &&
         y2 -. half_h <= y1 && y1 <= y2 +. half_h
    | (Rectangle (w, h), Point) ->
       let half_w = float_of_int w /. 2. in
       let half_h = float_of_int h /. 2. in
       x1 -. half_w <= x2 && x2 <= x1 +. half_w &&
         y1 -. half_h <= y2 && y2 <= y1 +. half_h
    | (Point, Square l) ->
       let half_l = float_of_int l /. 2. in
       x2 -. half_l <= x1 && x1 <= x2 +. half_l &&
         y2 -. half_l <= y1 && y1 <= y2 +. half_l
    | (Square l, Point) ->
       let half_l = float_of_int l /. 2. in
       x1 -. half_l <= x2 && x2 <= x1 +. half_l &&
         y1 -. half_l <= y2 && y2 <= y1 +. half_l
    (* circle, circle *)
    (* circle, rectangle ; rev*)
    (* circle, square ; rev *)
    (* rectangle, rectangle *)
    (* rectangle, square ; rev *)
    (* square, square *)
    | (_, _) -> false;;


(* exercise 6.3 *)
type nat = Zero | OneMoreThan of nat;;

let rec add m n =
  match m with
    | Zero -> n
    | OneMoreThan m' -> OneMoreThan (add m' n);;

let mul m n =
  let rec mul' m res =
    match m with
      | Zero -> res
      | OneMoreThan m' -> mul' m' (add res n)
  in mul' m Zero;;

let rec monus m n =
  match (m, n) with
    | (Zero, _) | (_, Zero) -> m
    | (OneMoreThan m', OneMoreThan n') -> monus m' n';;


(* exercise 6.4 *)
let rec minus m n =
  match (m, n) with
    | (_, Zero) -> Some m
    | (Zero, _) -> None
    | (OneMoreThan m', OneMoreThan n') -> minus m' n';;


(* exercise 6.5 *)
type 'a tree = Lf | Br of 'a * 'a tree * 'a tree;;

let rec size = function
  | Lf -> 0
  | Br (_, left, right) -> 1 + size left + size right;;

let rec depth = function
  | Lf -> 0
  | Br (_, left, right) -> 1 + max (depth left) (depth right);;


let rec comptree x = function
  | 0 -> Lf
  | n -> Br (x, comptree x (n - 1), comptree x (n - 1));;

let comptree' n =
  let rec make_node x = function
    | 0 -> Lf
    | n -> Br (x, make_node (2 * x) (n - 1), make_node (2 * x + 1) (n - 1))
  in make_node 1 n;;


(* exercise 6.6 *)
let rec inord t l =
  match t with
    | Lf -> l
    | Br (x, left, right) ->
       inord left (x:: (inord right l));;

let rec postord t l =
  match t with
    | Lf -> l
    | Br (x, left, right) ->
       postord left (postord right (x :: l));;


(* exersize 6.7 *)
let rec reflect = function
  | Lf -> Lf
  | Br (x, left, right) ->
     Br (x, reflect right, reflect left);;


(* exercise 6.10 *)
type arith =
    Const of int | Add of arith * arith | Mul of arith * arith;;

let rec eval = function
  | Const x -> x
  | Add (x, y) -> eval x + eval y
  | Mul (x, y) -> eval x * eval y;;

let exp = Mul (Add (Const 3, Const 4), Add (Const 2, Const 5));;
eval exp;;


(* exercise 6.11 *)
let rec string_of_arith = function
  | Const x -> string_of_int x
  | Add (x, y) -> "(" ^ string_of_arith x ^ "+" ^ string_of_arith y ^ ")"
  | Mul (x, y) -> "(" ^ string_of_arith x ^ "*" ^ string_of_arith y ^ ")";;

string_of_arith exp;;

let rec expand = function
  | Const x -> Const x
  | Add (x, y) -> Add (expand x, expand y)
  | Mul (Add (x, y), Add (z, w)) ->
     Add (Add (Mul (x, z), Mul (x, w)), Add (Mul (y, z), Mul (y, w)))
  | Mul (x, Add (y, z)) | Mul (Add (y, z), x) ->
     Add (Mul (expand x, expand y), Mul (expand x, expand z))
  | Mul (x, y) -> Mul (expand x, expand y);;

string_of_arith (expand exp);;


(* exercise 6.12 *)
[1; 2; 3; 4];;
[1; 2; 4; 3];;
[1; 3];;                                (* 2,4 は順不同最後*)
[1; 4; 2; 3];;
[1; 4; 3; 2];;
[2; 3; 4];;                             (* 1 は最初以外 *)
[2; 4; 3];;                             (* 1 は最初以外 *)
[3; 1; 2];;                             (* 4 は最初以外 *)
[3; 2; 1];;                             (* 4 は最初以外 *)
[4; 1; 2; 3];;
[4; 1; 3; 2];;
[4; 2];;                                (* 1,3 は順不同最後 *)
[4; 3; 1; 2];;
[4; 3; 2; 1];;

(* exercise 6.13 *)
type intseq = Cons of int * (int -> intseq);;

let rec nthseq n (Cons (x, f)) =
  if n = 1 then x
  else nthseq (n - 1) (f x);;

let nthfib n =
  let rec fib_pair n' (f1, f2) =
    if n' = 0 then (f1, f2)
    else fib_pair (n' - 1) (f2, f1 + f2) in
  let (f1', _) = fib_pair n (0, 1) in
  f1';;

let next_fib x =
  let rec next_fib' (f1, f2) =
    if f2 < x then next_fib' (f2, f1 + f2)
    else f2 in
  next_fib' (0, 1);;

let rec fib_seq x = Cons (next_fib (x + 1), fib_seq);;
let fib = fib_seq 0;;


(* exercise 6.14 *)
(* x-1 から 2  *)
let is_prime x =
  let rec is_divisible_from_2_to n =
    (n > 1) && ((x mod n = 0) || is_divisible_from_2_to (n - 1))
  in not (is_divisible_from_2_to (x - 1));;

let rec prime_seq x =
  if is_prime (x + 1) then Cons (x + 1, prime_seq) else prime_seq (x + 1);;

nthseq 3000 (prime_seq 1);;

(* 2 から x-1 *)
let is_prime x =
  let rec is_divisible i =
    (i < x) && ((x mod i = 0) || is_divisible (i + 1)) in
  not (is_divisible 2);;

let rec prime_seq x =
  if is_prime (x + 1) then Cons (x + 1, prime_seq) else prime_seq (x + 1);;

nthseq 3000 (prime_seq 1);;

(* 2 から sqrt(x) *)
let is_prime x =
  let last = int_of_float (floor (float_of_int x ** 0.5)) in
  let rec is_divisible i =
    (i <= last) && ((x mod i = 0) || is_divisible (i + 1)) in
  not (is_divisible 2);;

let rec prime_seq x =
  if is_prime (x + 1) then Cons (x + 1, prime_seq) else prime_seq (x + 1);;

nthseq 3000 (prime_seq 1);;

(* x より小さい素数だけ *)
let is_prime primes x =
  let rec is_divisible = function
    | [] -> false
    | p :: cdr -> (p < x) && ((x mod p = 0) || is_divisible cdr) in
  not (is_divisible primes);;

let rec prime_seq primes x =
  if is_prime primes (x + 1) then Cons (x + 1, prime_seq (primes @ [x + 1]))
  else prime_seq primes (x + 1);;

nthseq 3000 (prime_seq [] 1);;

(* sqrt(x) より小さい素数だけ *)
let is_prime primes x =
  let last = int_of_float (floor (float_of_int x ** 0.5)) in
  let rec is_divisible = function
    | [] -> false
    | p :: cdr -> (p <= last) && ((x mod p = 0) || is_divisible cdr) in
  not (is_divisible primes);;

let rec prime_seq primes x =
  if is_prime primes (x + 1) then Cons (x + 1, prime_seq (primes @ [x + 1]))
  else prime_seq primes (x + 1);;

nthseq 3000 (prime_seq [] 1);;


(* exercise 6.15 *)
type ('a, 'b) sum = Left of 'a | Right of 'b;;

let f1 = function
    | (a, Left b) -> Left (a, b)
    | (a, Right c) -> Right (a, c);;

let f2 = function
  | Left (a, b) -> (a, Left b)
  | Right (a, c) -> (a, Right c);;

let f3 = function
    | (Left a, Left c) -> Left (Left (a, c))
    | (Right b, Left c) -> Left (Right (b, c))
    | (Left a, Right d) -> Right (Left (a, d))
    | (Right b, Right d) -> Right (Right (b, d));;

let f4 = function
  | Left (Left (a, c)) -> (Left a, Left c)
  | Left (Right (b, c)) -> (Right b, Left c)
  | Right (Left (a, d)) -> (Left a, Right d)
  | Right (Right (b, d)) -> (Right b, Right d);;

let f5 (f1, f2) = function
  | Left a -> f1 a
  | Right c -> f2 c;;

(* f6 わからない? *)

let f7 s a =
  match s with
    | Left f1 -> Left (f1 a)
    | Right f2 -> Right (f2 a);;
