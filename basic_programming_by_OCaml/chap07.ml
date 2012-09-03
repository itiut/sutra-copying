(* exercise 7.1 *)
let sum_and_average a b c d e =
  let sum = a + b + c + d + e in
  (sum, sum / 5);;


(* exercise 7.3 *)
let x_axis_symmetry = function
  | (x, y) -> (x, -y);;

let test_x_axis_symmetry x y z = x_axis_symmetry (x, y) = z;;
test_x_axis_symmetry 0 0 (0, 0);;
test_x_axis_symmetry 1 1 (1, -1);;
test_x_axis_symmetry 5 ~-2 (5, 2);;


(* exercise 7.4 *)
let middle_point p1 p2 =
  match (p1, p2) with
    | ((x1, y1), (x2, y2)) -> ((x1 + x2) / 2, (y1 + y2) / 2);;

let test_middle_point p1 p2 z = middle_point p1 p2 = z;;
test_middle_point (0, 0) (0, 0) (0, 0);;
test_middle_point (0, 0) (2, 2) (1, 1);;
test_middle_point (-1, 1) (1, -1) (0, 0);;
