(* exercise 8.1-3 *)
type book_t = {
  title : string; auther : string; publisher : string; price : int; isbn: string
};;

type allowance_t = {
  bought_item : string; bought_price : int; bought_place : string; bought_date : string
};;

type person_t = {
  height : float; weight : float; birth_month : int; birth_day : int
};;


type student_t = {
  name : string; score : int; lank : string
};;


(* purpose: given empty string in lank, then evaluate lank by score *)
let evaluate = function
  | {name = n; score = s} ->
     let l =
       if s >= 80 then "A"
       else if s >= 70 then "B"
       else if s >= 60 then "C"
       else "D"
     in
     {name = n; score = s; lank = l};;

let test_evaluate n s l =
  evaluate {name = n; score = s; lank = ""} = {name = n; score = s; lank = l};;

test_evaluate "Bob" 90 "A";;
test_evaluate "Bob" 80 "A";;
test_evaluate "Bob" 79 "B";;
test_evaluate "Bob" 70 "B";;
test_evaluate "Bob" 69 "C";;
test_evaluate "Bob" 60 "C";;
test_evaluate "Bob" 59 "D";;


(* exercise 8.5 *)
type station_t = {
  name_kanji : string; name_kana : string; name_roman : string; train_line : string;
};;

(* exercise 8.6 *)
let show_station_name = function
  | {name_kanji = kanji; name_kana = kana; train_line = line} ->
     line ^ ", " ^ kanji ^ " (" ^ kana ^ ")";;

let test_show_station_name kanji kana line =
  show_station_name {name_kanji = kanji; name_kana = kana; name_roman = ""; train_line = line}
    = line ^ ", " ^ kanji ^ " (" ^ kana ^ ")";;

test_show_station_name "茗荷谷" "みょうがだに" "丸ノ内線";;


(* exercise 8.7 *)
type connection_t = {
  start_station : station_t;
  end_station : station_t;
  via : string;
  distance_km : float;
  time_required_m : int;
};;
