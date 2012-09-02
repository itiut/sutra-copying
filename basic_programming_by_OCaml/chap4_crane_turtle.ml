(* purpose:
   given the number of cranes and turtles, and their legs,
   calculate the number of cranes *)
(* crane_turtle : int -> int -> int *)
let crane_turtle num leg =
  (4 * num - leg) / 2

(* test *)
let test x y z = crane_turtle x y = z;;

test 0 0 0;;
test 1 2 1;;
test 1 4 0;;
test 2 4 2;;
test 2 6 1;;
test 2 8 0;;
test 10 30 5;;
