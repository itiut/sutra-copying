(* exe4.1 *)
let curry f x y = f (x, y);;

let average (x, y) = (x +. y) /. 2.0;;

let curried_ave = curry average;;

let uncurry f (x, y) = f x y;;

let ave = uncurry curried_ave;;


(* exe4.2 *)
let rec repeat f n x =
  if n > 0 then repeat f (n - 1) (f x) else x;;

let fib n =
  let (fibn, _) = repeat (fun (f1, f2) -> (f2, f1 + f2)) n (0, 1)
  in fibn;;
