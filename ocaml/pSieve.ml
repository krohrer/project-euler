open Printf
module B = Bitarray
module V = Vector

type t = {
  mutable cutoff : int;
  sieve : B.t;
  primes : int V.t
}

let cutoff p = p.cutoff

let make n =
  let sieve = B.make (n-1) true in
  let primes = V.make () in
  for i = 2 to n do
    if B.get sieve (i-2) then begin
      for k = 2*i to n/i do
	B.set sieve (k*i-2) false
      done;
      V.insert_last primes i
    end
  done;
  {
    cutoff = n;
    sieve;
    primes
  }

let grow_to p i =
  printf "PSieve: Growing to %i" i;
  let n = p.cutoff in
  let n_new = max (2*n) i in (* grow exponentially *)
  B.resize p.sieve (n_new-1) true;
  for i = 2 to n do
    if B.get p.sieve (i-2) then begin
      for k = n/i + 1 to n_new/i do
	B.set p.sieve (k*i-2) false
      done
    end
  done;
  for i = n+1 to n_new do
    if B.get p.sieve (i-2) then begin
      for k = 2*i to n_new/i do
	B.set p.sieve (k*i-2) false
      done;
      V.insert_last p.primes i
    end
  done;
  p.cutoff <- n_new

let is_prime p i =
  if i < 2 then false else begin
    if p.cutoff < i then grow_to p i;
    B.get p.sieve i
  end

let primes p i =
  if p.cutoff < i then grow_to p i;
  V.to_array p.primes
