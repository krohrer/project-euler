(* 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

   Find the sum of all numbers which are equal to the sum of the
   factorial of their digits.

   Note: as 1! = 1 and 2! = 2 are not sums they are not included.


   What is the highest number of digits that would still be possible?

   The highest summand is 9! = 362880

   We group numbers by number of digits D

   sum = 0
   For each group:
	keep_looking = false
   	Enumerate all numbers x in group:
   		Calculate sum of digit factorials
   		If sum == x then:
			add x to sum
   		keep_looking = keep_looking || x <= sum
*)

open Printf

let sum_fac x = 
  Numbers.digits_fold (fun sum x -> Numbers.fac x + sum) 0 x

let rec fold_over_groups ~x ~x_10 ~s_max ~sum =
  if x < x_10 then
    let s_f = sum_fac x in
    let s_max = max s_max s_f in
    let sum = sum + 
      if s_f = x then begin
	printf "Found curious number %i\n%!" x;
	x
      end else
	0
    in
    fold_over_groups ~x:(x+1) ~x_10 ~s_max ~sum
  else
    if x_10 < s_max then
      let x_10 = x_10 * 10 in
      fold_over_groups ~x ~x_10 ~s_max ~sum
    else
      sum

let _ =
  printf "Solution = %i\n" (fold_over_groups ~x:10 ~x_10:1000 ~s_max:0 ~sum:0)
