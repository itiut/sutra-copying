(* exercise 4.1 *)
let monthly_pay year hour =
  let hourly_pay = 850 + 100 * year in
  hourly_pay * hour;;

(* exercise 4.2 *)
let introduce name =
  "I am " ^ name ^ ". Ask me anything.";;

(* exercise 4.3 *)
let normal_weight height =
  height ** 2.0 *. 22.0;;

(* exercise 4.4 *)
let bmi height weight =
  weight /. (height ** 2.0);;
