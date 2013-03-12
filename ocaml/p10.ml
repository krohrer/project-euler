open Printf

let _ =
  assert (Sys.word_size > 32);
  let n = 1999999 in
  let ps = PSieve.make n in
  let primes = PSieve.primes ps n in
  let sum = Array.fold_left (+) 0 primes in
  printf "Solution = %i\n" sum
