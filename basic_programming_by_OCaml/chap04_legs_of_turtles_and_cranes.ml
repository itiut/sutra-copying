(* purpose: calculate legs of turtles and cranes *)
(* legs_of_turtles_and_cranes : int -> int -> int *)
let legs_of_turtles_and_cranes crane turtle =
  crane * 2 + turtle * 4

(* test *)
let test x y z = legs_of_turtles_and_cranes x y = z;;

test 0 0 0;;
test 1 0 2;;
test 0 1 4;;
test 1 2 10;;
test 3 10 46;;
