open Printf

let _ = assert (Sys.word_size > 32)

let _ =
  let n = 600851475143 in
  let sqrt_n = int_of_float (sqrt (float_of_int n)) + 1 in
  let ps = PSieve.make sqrt_n in
  let primes = PSieve.primes_upto ps sqrt_n in
  let rec search = function
    | i when i >= 0 ->
      let p = primes.(i) in
      if n mod p = 0 then p else search (i-1)
    | _ -> n
  in
  printf "Solution = %i\n" (search (Array.length primes - 1))
