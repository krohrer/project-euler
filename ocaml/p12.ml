open Printf

let _ = 
  let p = PSieve.make 10000 in
  (* divisor count of i*(i-1)/2, basic combinatorics :) *)
  let rec tri_divisor_count p f1 f2 =
    match f1, f2 with
    | [], [] -> p
    | [], (_,e)::r
    | (_,e)::r, [] -> tri_divisor_count ((e+1)*p) [] r
    | (p1,e1)::r1, (p2,e2)::r2 ->
      (* adjust for division by 2 *)
      let adjust = if p1 = 2 || p2 = 2 then -1 else 0 in
      if p1 < p2 then
	tri_divisor_count ((e1+1+adjust)*p) r1 f2
      else if p2 < p1 then
	tri_divisor_count ((e2+1+adjust)*p) f1 r2
      else (* p1 = p2 *)
	tri_divisor_count ((e1+e2+1+adjust)*p) r1 r2
  in
  let rec search i pf1 =
    let pf2 = PSieve.prime_factors p i in
    let d = tri_divisor_count 1 pf1 pf2 in
    let t = i*(i-1)/2 in
    if 500 < d then
      printf "Solution = %i\n" t
    else
      search (i+1) pf2
  in
  search 3 (PSieve.prime_factors p 2)
