(* exercise 5.2 *)
(* ampm : int -> string *)
let ampm hour =
  if (hour mod 24) < 12 then "AM" else "PM"

(* test *)
let test_ampm x y = ampm x = y;;
test_ampm 0 "AM";;
test_ampm 1 "AM";;
test_ampm 11 "AM";;
test_ampm 12 "PM";;
test_ampm 23 "PM";;
test_ampm 24 "AM";;


(* exercise 5.3 *)
(* constellation : int -> int -> string *)
let constellation month day =
  let t = [(1, 19, "Capricornus"); (2, 17, "Aquarius"); (3, 19, "Pisces");
           (4, 19, "Aries"); (5, 20, "Taurus"); (6, 20, "Gemini");
           (7, 21, "Cancer"); (8, 22, "Leo"); (9, 21, "Virgo");
           (10, 22, "Libra"); (11, 21, "Scorpio"); (12, 20, "Sagittarius")] in
  let rec loop = function
    | [] -> let (_, _, name) = List.hd t in name
    | (m, d, name) :: tl ->
       if month < m || (month = m && day <= d) then name
       else loop tl
  in
  loop t;;

(* test *)
let test_constellation x y z = constellation x y = z;;
test_constellation 1 2 "Capricornus";;
test_constellation 2 17 "Aquarius";;
test_constellation 2 20 "Pisces";;
test_constellation 3 20 "Aries";;


(* exercise 5.4 *)
(* discriminant : float -> float -> float -> float *)
let discriminant a b c = b ** 2.0 -. 4.0 *. a *. c;;

(* test *)
let test_discriminant a b c d = discriminant a b c = d;;
test_discriminant 1.0 2.0 1.0 0.0;;
test_discriminant 1.0 4.0 2.0 8.0;;


(* exercise 5.5 *)
(* num_solution : flaot -> float -> float -> int *)
let num_solution a b c =
  match discriminant a b c with
    | d when d > 0.0 -> 2
    | d when d = 0.0 -> 1
    | _ -> 0

let test_num_solution a b c x = num_solution a b c = x;;
test_num_solution 1.0 2.0 1.0 1;;
test_num_solution 1.0 4.0 1.0 2;;
test_num_solution 1.0 0.0 1.0 0;;


(* exercise 5.6 *)
(* imaginary_solutions_exist : float -> float -> float -> bool *)
let imaginary_solutions_exist a b c =
  if discriminant a b c < 0.0 then true else false

let test_imaginary_solutions_exist a b c x = imaginary_solutions_exist a b c = x;;
test_imaginary_solutions_exist 1.0 4.0 1.0 false;;
test_imaginary_solutions_exist 1.0 2.0 1.0 false;;
test_imaginary_solutions_exist 1.0 1.0 1.0 true;;


(* exercise 5.7 *)
(* physique : float -> float -> string *)
let physique height weight =
  let bmi h w = w /. h ** 2.0 in
  match bmi height weight with
    | x when x < 18.5 -> "thin"
    | x when x < 25.0 -> "normal"
    | x when x < 30.0 -> "fat"
    | _ -> "extremely fat";;

let test_physique a b x = physique a b = x;;
test_physique 1.72 55.5 "thin";;
test_physique 1.72 55.5 "normal";;
test_physique 1.75 180.2 "extremely fat";;
