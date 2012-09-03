let sum l =
  let rec sum' s = function
    | [] -> s
    | hd :: tl -> sum' (hd + s) tl
  in
  sum' 0 l;;


(* exercise 9.4 *)
let length li =
  let rec length' len = function
    | [] -> len
    | hd :: tl -> length' (len + 1) tl
  in
  length' 0 li;;


(* exercise 9.5 *)
let rec even = function
  | [] -> []
  | hd :: tl ->
     if hd mod 2 = 0 then hd :: even tl
     else even tl;;


(* exercise 9.6 *)
let rec concat = function
  | [] -> ""
  | hd :: tl -> hd ^ concat tl;;


(* esercise 9.7 *)
type person_t = {
  height : float;
  weight : float;
  birth_month : int;
  birth_day : int;
  blood_type : string;
};;

let count_blood_type_A person =
  let rec count cur = function
    | [] -> cur
    | {blood_type = "A"} :: tl -> count (cur + 1) tl
    | _ :: tl -> count cur tl
  in
  count 0 person;;
