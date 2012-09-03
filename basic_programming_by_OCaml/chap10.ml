let rec add_to_each x = function
  | [] -> []
  | hd :: tl -> (x :: hd) :: add_to_each x tl;;

let test_add_to_each x li z =
  add_to_each x li = z;;

test_add_to_each 1 [] [];;
test_add_to_each 1 [[2]] [[1;2]];;
test_add_to_each 1 [[2]; [2;3]] [[1;2]; [1;2;3]];;
test_add_to_each 1 [[2]; [2;3]; [2;3;4]] [[1;2]; [1;2;3]; [1;2;3;4]];;


let rec prefix = function
  | [] -> []
  | hd :: tl -> [hd] :: add_to_each hd (prefix tl);;

let test_prefix li z =
  prefix li = z;;

test_prefix [] [];;
test_prefix [1] [[1]];;
test_prefix [1;2] [[1]; [1;2]];;
test_prefix [1;2;3;4] [[1]; [1;2]; [1;2;3]; [1;2;3;4]];;


(* exercise 10.1 *)
let rec insert li n =
  match li with
    | [] -> [n]
    | hd :: tl ->
       if n < hd then n :: hd :: tl
       else hd :: insert tl n;;


(* exercise 10.2 *)
let rec ins_sort = function
  | [] -> []
  | hd :: tl -> insert (ins_sort tl) hd;;


(* exercise 10.3 *)
type student_t = {
  name : string; score : int; lank : string
};;

let student_sort li =
  let rec insert student = function
    | [] -> [student]
    | hd :: tl ->
       if student.score < hd.score then student :: hd :: tl
       else hd :: insert student tl in
  let rec ins_sort = function
    | [] -> []
    | hd :: tl -> insert hd (ins_sort tl) in
  ins_sort li;;


(* section 10.2 *)
let rec minimum = function
  | [] -> raise (Invalid_argument "empty list")
  | hd :: [] -> hd
  | hd :: tl -> min hd (minimum tl);;


(* exercise 10.7 *)
type person_t = {
  height : float;
  weight : float;
  birth_month : int;
  birth_day : int;
  blood_type : string;
};;

let rec histogram_blood_type = function
  | [] -> (0, 0, 0, 0)
  | {blood_type = blood} :: tl ->
     let (a, b, o, ab) = histogram_blood_type tl in
     match blood with
       | "A" -> (a+1, b, o, ab)
       | "B" -> (a, b+1, o, ab)
       | "O" -> (a, b, o+1, ab)
       | _ -> (a, b, o, ab+1);;


(* section 10.5 *)
let rec append li1 li2 =
  match li1 with
    | [] -> li2
    | hd :: tl -> hd :: (append tl li2);;


(* section 10.6 *)
let rec merge li1 li2 =
  match (li1, li2) with
    | ([], []) -> []
    | (([], li) | (li, [])) -> li
    | (hd1 :: tl1, hd2 :: tl2) ->
       if hd1 < hd2 then hd1 :: (merge tl1 li2)
       else hd2 :: (merge li1 tl2);;


(* exercise 10.9 *)
let rec equal_length li1 li2 =
  match (li1, li2) with
    | ([], []) -> true
    | (([], _) | (_, [])) -> false
    | (hd1 :: tl1, hd2 :: tl2) -> equal_length tl1 tl2;;
