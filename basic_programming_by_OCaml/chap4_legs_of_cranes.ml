(* purpose: calculate legs of cranes *)
(* legs_of_cranes : int -> int *)
let legs_of_cranes num_crane = num_crane * 2;;

(* test *)
let test_legs_of_cranes x y = legs_of_cranes x = y;;

test_legs_of_cranes 0 0;;
test_legs_of_cranes 1 2;;
test_legs_of_cranes 3 6;;
test_legs_of_cranes 10 20;;
