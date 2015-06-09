(* A perfect number is a number for which the sum of its proper
   divisors is exactly equal to the number. For example, the sum of the
   proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means
   that 28 is a perfect number.

   A number n is called deficient if the sum of its proper divisors is
   less than n and it is called abundant if this sum exceeds n.

   As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the
   smallest number that can be written as the sum of two abundant numbers
   is 24. By mathematical analysis, it can be shown that all integers
   greater than 28123 can be written as the sum of two abundant
   numbers. However, this upper limit cannot be reduced any further by
   analysis even though it is known that the greatest number that cannot
   be expressed as the sum of two abundant numbers is less than this
   limit.

   Find the sum of all the positive integers which cannot be written as
   the sum of two abundant numbers.
*)

open Printf
module V = Vector

let _ = 
  let n = 28123 in
  let ds = Array.create n 1 in
  let vas = V.make () in

  let is_abundant i = i < ds.(i-1) in

  ds.(0) <- 0;
  for i = 2 to n do
    if is_abundant i then V.push_back vas i;
    for k = 2 to n/i do
      ds.(k*i-1) <- ds.(k*i-1) + i
    done
  done;
  let abundants = V.to_list vas in

  let is_abundant_sum i =
    let rec loop = function
      | a::rest when a < i -> is_abundant (i - a) || loop rest
      | _ -> false
    in
    loop abundants
  in

  let sum = ref 0 in
  for i = 1 to n do
    if not (is_abundant_sum i) then
      sum := !sum + i
  done;
  printf "Solution = %i\n" !sum
