(* hourly pay (yen) *)
let hourly_pay = 950

(* base salary (yen) *)
let base_salary = 100

(* purpose: calculate salary by working hours x *)
(* salary : int -> int *)
let salary x = base_salary + x * hourly_pay

(* test *)
let test_salary x y = salary x = y;;

test_salary 25 23850;;
test_salary 28 26700;;
test_salary 31 29550;;
