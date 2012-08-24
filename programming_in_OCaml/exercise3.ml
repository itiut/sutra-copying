(* exe3.1 *)
let yen_per_dollar = 114.32;;

let dollar_to_yen dollar =
  int_of_float (dollar *. yen_per_dollar +. 0.5);;

let yen_to_dollar yen =
  float_of_int (int_of_float (float_of_int yen /. yen_per_dollar +. 0.5));;

let string_of_yen_of_dollar dollar =
  string_of_float dollar ^ " dollars are " ^ string_of_int (dollar_to_yen dollar) ^ " yen.";;

let capitalize char =
  if char < 'A' || 'Z' < char then char
  else let alphabet_offset = int_of_char char - int_of_char 'A' in
       char_of_int (int_of_char 'a' + alphabet_offset);;


(* exe3.2 *)
let expand_and_1 b1 b2 =
  if b1 then b2 else false;;

let expand_or_1 b1 b2 =
  if b1 then true else b2;;


(* exe3.3 *)
let expand_and_2 b1 b2 =
  not ((not b1) || (not b2));;

let expand_or_2 b1 b2 =
  not ((not b1) && (not b2));;


(* exe3.4 *)
let x = 1 in let x = 3 in let x = x + 2 in x * x;;

let x = 2 and y = 3 in (let y = x and x = y + 2 in x * y) + y;;

let x = 2 in let y = 3 in let y = x in let z = y + 2 in x * y * z;;


(* exe3.6 *)
let geo_mean (x, y) =
  sqrt (x *.y);;

let bmi_message (name, height, weight) =
  let bmi = weight /. (height ** 2.0) in
  if bmi < 18.5 then name ^ " is thin."
  else if bmi < 25.0 then name ^ " is healthy."
  else if bmi < 30.0 then name ^ " is fat."
  else name ^ " is extremely fat.";;

let f (sum, diff) =
  ((sum + diff) / 2, (sum - diff) / 2);;
