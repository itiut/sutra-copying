(* section 17.3 *)
type tree_t = Empty | Leaf of int | Node of int * tree_t * tree_t;;

let rec sum_tree = function
  | Empty -> 0
  | Leaf x -> x
  | Node (x, left, right) -> x + sum_tree right + sum_tree left;;


(* exercise 17.5 *)
let rec tree_double = function
  | Empty -> Empty
  | Leaf x -> Leaf (2 * x)
  | Node (x, left, right) -> Node (2 * x, tree_double left, tree_double right);;


(* exercise 17.6 *)
let rec tree_map f = function
  | Empty -> Empty
  | Leaf x -> Leaf (f x)
  | Node (x, left, right) -> Node (f x, tree_map f left, tree_map f right);;


(* exercise 17.7 *)
let rec tree_length = function
  | Empty -> 0
  | Leaf _ -> 1
  | Node (_, left, right) -> 1 + tree_length left + tree_length right;;


(* exercise 17.8 *)
let rec tree_depth = function
  | Empty -> 0
  | Leaf _ -> 1
  | Node (_, left, right) -> 1 + max (tree_depth left) (tree_depth right);;


(* section 17.4 *)
let rec binary_search tree data =
  match tree with
    | Empty -> false
    | Leaf x -> data = x
    | Node (x, left, right) ->
       if data = x then true
       else if data < x then binary_search left data
       else binary_search right data;;

let rec binary_insert tree data =
  match tree with
    | Empty -> Leaf data
    | Leaf x ->
       if data = x then Leaf data
       else if data < x then Node (x, Leaf data, Empty)
       else Node (x, Empty, Leaf data)
    | Node  (x, left, right) ->
       if data = x then Node (x, left, right)
       else if data < x then Node (x, binary_insert left data, right)
       else Node (x, left, binary_insert right data);;
