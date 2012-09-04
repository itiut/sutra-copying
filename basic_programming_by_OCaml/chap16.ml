(* exercise 16.1 *)
let sum_list li =
  let rec sum_list' sum = function
    | [] -> []
    | hd :: tl -> (sum + hd) :: sum_list' (sum + hd) tl
  in sum_list' 0 li;;


(* section 16.3 *)
let reverse li =
  let rec reverse' rev = function
    | [] -> rev
    | hd :: tl -> reverse' (hd :: rev) tl
  in reverse' [] li;;


(* exercise 16.2 *)
let fold_left f init li =
  let rec fold_left' cur = function
    | [] -> cur
    | hd :: tl -> fold_left' (f cur hd) tl
  in fold_left' init li;;
