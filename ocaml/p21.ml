(* Let d(n) be defined as the sum of proper divisors of n (numbers
   less than n which divide evenly into n).  If d(a) = b and d(b) = a,
   where a <> b, then a and b are an amicable pair and each of a and b are
   called amicable numbers.

   For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20,
   22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284
   are 1, 2, 4, 71 and 142; so d(284) = 220.

   Evaluate the sum of all the amicable numbers under 10000.
*)
open Printf

let _ =
  let n = 10000-1 in
  let dsums = Array.create n 1 in
  dsums.(0) <- 0;
  for i = 2 to n do
    for k = 2 to n/i do
      dsums.(k*i-1) <- dsums.(k*i-1) + i
    done
  done;
  let sum = ref 0 in
  for i = 2 to n do
    let d = dsums.(i-1) in
    if d <= n && dsums.(d-1) = i && d < i then begin
      sum := !sum + d + i
    end
  done;
  printf "Solution = %i\n" !sum
