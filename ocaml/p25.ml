open Printf

let _ =
  Num.(
    let limit = Int 10 **/ Int (1000-1) in
    let rec fib i f1 f2 =
      let f3 = f1 +/ f2 in
      if f3 </ limit then
	fib (i+1) f2 f3
      else
	i, f3
    in
    let i, f = fib 3 (Int 1) (Int 1) in
    printf "%s\n" (string_of_num f);
    printf "Solution = %u\n" i
  )
