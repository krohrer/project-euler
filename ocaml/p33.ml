open Printf

let qeq (n1,d1) (n2,d2) =
  n1*d2 = n2*d1

let qcanon (n,d) = 
  let g = Numbers.gcd n d in
  (n/g,d/g)

let qmul (n1,d1) (n2,d2) =
  qcanon (n1*n2,d1*d2)

let qprint outc (n,d) =
  fprintf outc "%d/%d" n d

let qnum = fst and
    qdenom = snd

let _ =
  let rec search p n x d =
    match n, x, d with
    | _, _, 10 -> search p n (x+1) 1
    | _, 10, d -> search p (n+1) 1 d
    | 10, _, _ -> p
    | _ ->
      let (nom,denom) as f = (10*n + x,
			      10*x + d) in
      let p =
	if nom < denom && qeq f (n,d) then
	  qmul p f
	else
	  p
      in
      search p n x (d+1)
  in
  printf "Solution = %d\n" (qdenom (search (1,1) 1 1 1))
