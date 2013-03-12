open Printf
module B = Bitarray
module V = Vector

type t = {
  mutable ceiling : int;
  sieve : B.t;
  primes : int V.t;
}

let ceiling p = p.ceiling

let prime_count p = V.count p.primes

let make n =
  let sieve = B.make (n-1) true in
  let primes = V.make () in
  for i = 2 to n do
    if B.get sieve (i-2) then begin
      for k = 2 to n/i do
	B.set sieve (k*i-2) false
      done;
      V.insert_last primes i
    end
  done;
  {
    ceiling = n;
    sieve;
    primes
  }

let grow_to p i =
  printf "PSieve: Growing to %i\n" i;
  let n = p.ceiling in
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
      for k = 2 to n_new/i do
	B.set p.sieve (k*i-2) false
      done;
      V.insert_last p.primes i
    end
  done;
  p.ceiling <- n_new

let is_prime p i =
  if i < 2 then false else begin
    if p.ceiling < i then grow_to p i;
    B.get p.sieve (i-2)
  end

let get_prime p idx =
  while prime_count p <= idx do
    (* Grow exponentially *)
    grow_to p (2 * ceiling p)
  done;
  V.get p.primes idx

let primes p i =
  if p.ceiling < i then grow_to p i;
  V.to_array p.primes

let prime_factors p n =
  let rec consume i rem fl =
    if rem < 2 then
      fl
    else if is_prime p rem then
      (* If the remainder is prime, do not look further *)
      (rem,1)::fl
    else begin
      (* Try next prime *)
      let p = get_prime p i in
      let rem, exp =
	let rec calc rem exp =
	  if rem mod p = 0 then
	    calc (rem/p) (exp+1)
	  else
	    rem, exp
	in
	calc rem 0
      in
      if 0 < exp then
	consume (i + 1) rem ((p,exp)::fl)
      else
	consume (i + 1) rem fl
    end
  in
  List.rev (consume 0 n [])

let divisor_count p n =
  let pfs = prime_factors p n in
  List.fold_left (fun p (_,e) -> p * (e + 1)) 1 pfs
