open Printf

let _ =
  let ps = PSieve.make 103 in
  Array.iter (fun p -> printf "%i is prime.\n" p) (PSieve.primes ps 100)
  
