open Printf

let is_sum_of_power_of_digits ~exp = function
  | i when i > 1 ->
    let sum = ref 0 in
    let r = ref i in
    while !r > 0 && !sum < i do
      let d = !r mod 10 in
      sum := !sum + Numbers.pow d exp;
      r := !r / 10
    done;
    !r = 0 && !sum = i
  | _ -> false

let max_digits_for_power ~exp =
  let d = ref 1 in
  while Numbers.pow 10 !d < !d * (Numbers.pow 9 exp) do
    d := !d + 1
  done;
  !d

let upper_bound_for_power ~exp =
  let ds = max_digits_for_power ~exp in
  ds * Numbers.pow 9 exp

let _ =
  let exp = 5 in
  let sum = ref 0 in
  for i = 0 to upper_bound_for_power ~exp do
    if is_sum_of_power_of_digits ~exp i then (
      printf "%d\n" i;
      sum := !sum + i
    )
  done;
  printf "Solution = %d\n" !sum
