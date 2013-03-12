let _ =
  let n = 10001 in
  let ps = PSieve.make n in
  Printf.printf "Solution = %i" (PSieve.get_prime ps (n-1))

