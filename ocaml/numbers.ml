let gcd a b =
  let rec loop a = function
    | 0 -> a
    | b -> loop b (a mod b)
  in
  loop a b
  
let gcd_fold1 = function
  | [] -> invalid_arg "Numbers.gcd_fold1"
  | x :: rest -> List.fold_left gcd x rest
