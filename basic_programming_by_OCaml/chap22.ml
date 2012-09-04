(* exercise 22.2 *)
let fib_array array =
  let arr = Array.copy array in
  let rec fill_fib_array i =
    arr.(i) <- arr.(i - 1) + arr.(i - 2);
    fill_fib_array (i + 1)
  in try
       arr.(0) <- 0;
       arr.(1) <- 1;
       fill_fib_array 2
    with Invalid_argument _ -> arr;;
