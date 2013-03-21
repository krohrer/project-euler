open Printf
(*
  n*n + a*n + b = prime(x)

  CASE n=0:
  0*0 + a*0 + b = prime(x_1)
  I: b = prime(x_1)
  II: abs b < 1000 => -1000 < b && b < 1000
  I & II:
  => prime(x_1) < 1000

  CASE n=1:
  1*1 + a*1 + b = prime(x_2)

  a = p2 - b - 1
  
  I: a + b + 1 = prime(x_2)
  II: abs a < 1000 => -1000 < a && a < 1000
  I & II:
  => -1000 + b + 1 < a + b + 1 = prime(x_2) < 1000 + b + 1
  => -1000 + b + 1 < prime(x_2) < 1000 + b + 1
*)


let _ =
  let dim = 1000 in
  let module P = PSieve.Default in
  let quadratic a b n = n*n + a*n + b in
  let rec length_of_series a b n =
    let x = quadratic a b n in
    if P.is_prime x then
      length_of_series a b (n+1)
    else
      n
  in
  let maxlen = ref 0 and
      coeffs = ref (0,0) in
  let rec search_b x1 =
    let p1 = P.get_prime x1 in
    let b = p1 in
    if b < dim then (
      let rec search_a x2 =
	let p2 = P.get_prime x2 in
	let a = p2 - b - 1 in
	if abs a < dim then (
	  let len = length_of_series a b 2 in
	  (* assert (length_of_series a b 0 = len); *)
	  if len > !maxlen then (
	    maxlen := len;
	    coeffs := a, b
	  );
	  search_a (x2+1)
	)
      in
      let _, x2 = P.get_prime_after (~-dim + p1 + 1) in
      search_a x2;
      search_b (x1+1)
    )
  in
  search_b 0;
  let print_series a b =
    printf "n*n + %d*n + %d:\n" a b;
    let rec loop i =
      let x = quadratic a b i in
      if P.is_prime x then (
  	printf " %d" x;
  	loop (i+1)
      )
    in
    loop 0;
    printf "\nlen = %d\n" (length_of_series a b 2)
  in
  let a, b = !coeffs in
  printf "Solution = %d\n" (a*b);
  print_series a b
