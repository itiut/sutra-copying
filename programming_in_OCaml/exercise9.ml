(* section 9.2 *)
module Tree =
  struct
    type 'a t = Lf | Br of 'a * 'a t * 'a t

    let rec size = function
      | Lf -> 0
      | Br (_, left, right) -> 1 + size left + size right

    let rec depth = function
      | Lf -> 0
      | Br (_, left, right) -> 1 + max (depth left) (depth right)
  end;;


(* section 9.3 *)
module Table =
  struct
    type ('a, 'b) t = Empty | Entry of 'a * 'b * ('a, 'b) t

    let empty = Empty

    let add key value table = Entry (key, value, table)

    let rec retrieve key = function
      | Empty -> None
      | Entry (key', value, rest) ->
         if key' = key then Some value else retrieve key rest

    let rec delete key = function
      | Empty -> Empty
      | Entry (key', value, rest) ->
         if key = key' then delete key rest
         else Entry (key', value, delete key rest)

    let rec dump = function
      | Empty -> []
      | Entry (key, value, rest) ->
         (key, value) :: (dump (delete key rest))
  end;;

let ( <<< ) table (key, value) = Table.add key value table;;

let table = Table.Empty
  <<< ("a", "the first letter of the English alphabet")
  <<< ("b", "the second letter of the English alphabet")
  <<< ("zzz", "sleeping noise");;

Table.retrieve "a" table;;

let table' = table <<< ("a", "an indefinite article");;

Table.retrieve "a" table';;

Table.dump table';;

Table.delete "a" table';;


module type TABLE1 =
  sig
    type ('a, 'b) t = Empty | Entry of 'a * 'b * ('a, 'b) t
    val epmty : ('a, 'b) t
    val add : 'a -> 'b -> ('a, 'b) t -> ('a, 'b) t
    val retrieve : 'a -> ('a, 'b) t -> 'b option
    val dump : ('a, 'b) t -> ('a * 'b) list
  end;;

module Table1 : TABLE1 = Table;;


module type TABLE2 =
  sig
    type ('a, 'b) t
    val epmty : ('a, 'b) t
    val add : 'a -> 'b -> ('a, 'b) t -> ('a, 'b) t
    val retrieve : 'a -> ('a, 'b) t -> 'b option
    val dump : ('a, 'b) t -> ('a * 'b) list
  end;;

module Table2 : TABLE2 = Table;;


(* exercise 9.1 *)
