let gcd a b =
  let rec loop a = function
    | 0 -> a
    | b -> loop b (a mod b)
  in
  loop a b
  
let gcd_fold1 = function
  | [] -> invalid_arg "Numbers.gcd_fold1"
  | x :: rest -> List.fold_left gcd x rest

let rec pow n = function
  | 0 -> 1
  | 1 -> n
  | e when e < 0 -> invalid_arg "Numbers.pow: negative exponent."
  | e when e mod 2 == 0 -> (* even numbers *)
    let p = pow n (e/2) in
    p * p
  | e -> n * pow n (e-1)

let fac n =
  let rec loop p = function
    | i when i > 0 ->
      loop (p*i) (i-1)
    | _ -> p
  in
  loop 1 n
