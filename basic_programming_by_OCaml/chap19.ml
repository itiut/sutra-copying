module Tree = struct
  type ('a, 'b) t =
    | Empty
    | Node of ('a, 'b) t * 'a * 'b * ('a, 'b) t

  let empty = Empty

  let rec insert tree k v =
    match tree with
      | Empty -> Node (Empty, k, v, Empty)
      | Node (left, key, value, right) ->
         if k < key then Node (insert left k v, key, value, right)
         else Node (left, key, value, insert right k v)

  let rec search tree k =
    match tree with
      | Empty -> raise Not_found
      | Node (left, key, value, right) ->
         if k = key then value
         else if k < key then search left k
         else search right k
end;;


module type Tree_t = sig
  type ('a, 'b) t
  val empty : ('a, 'b) t
  val insert : ('a, 'b) t -> 'a -> 'b -> ('a, 'b) t
  val search : ('a, 'b) t -> 'a -> 'b
end;;

module NewTree = (Tree : Tree_t);;
