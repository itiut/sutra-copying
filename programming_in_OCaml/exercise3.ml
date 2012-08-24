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


(* exe3.7 *)
let rec pow_1 (x, n) =
  if n = 0 then 1.0 else x *. pow_1 (x, n - 1);;

let rec pow_2 (x, n) =
  if n = 0 then 1.0
  else if n mod 2 = 0 then pow_2 (x ** 2.0, n / 2)
  else x *. pow_2 (x ** 2.0, (n - 1) / 2);;


(* exe3.8 *)
let rec pow_3 (x, n) =
  let rec iterpow (i, res) =
    if i > n then res
    else iterpow (i + 1, res * x)
  in
  iterpow (1, 1);;


(* exe3.11 *)
let rec gcd (m, n) =
  let (m, n) = if m >= n then (m, n) else (n, m) in
  if n = 0 then m else gcd (n, m mod n);;

let rec comb (n, m) =
  if m = 0 || m = n then 1
  else comb (n - 1, m) + comb (n - 1, m - 1);;

let fib n =
  let rec iterfib (i, n, f1, f2) =
    if i > n then f2
    else iterfib (i + 1, n, f1 + f2, f1)
  in
  iterfib (1, n, 1, 0);;

let max_ascii str =
  let n = String.length str in
  let rec iter_max_ascii (i, max_char) =
    if i >= n then max_char
    else let max_char = if str.[i] > max_char then str.[i] else max_char in
         iter_max_ascii (i + 1, max_char)
  in
  iter_max_ascii (0, '\000');;


(* exe3.12 *)
let rec pos n =
  if n < 0 then 0.0
  else pos (n - 1) +. 1.0 /. (float_of_int (4 * n + 1)) -. 1.0 /. (float_of_int (4 * n + 3));;


(* exe3.13 *)
let pow_curry n =
  fun x -> pow_2 (x, n);;

let cube = pow_curry 3;;


(* exe3.14 *)
let integral f a b =
  let dx = 1e-5 in
  let rec loop x res =
    if x > b then res
    else loop (x +. dx) (res +.(f x +. f (x +. dx)) *. dx /. 2.0)
  in loop a 0.0;;
