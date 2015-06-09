open Printf
module B = Bitarray
module V = Vector

type t = {
  mutable ceiling : int;
  sieve : B.t;
  primes : int V.t;
}

type index = int

let ceiling sieve = sieve.ceiling

let prime_count sieve = V.count sieve.primes

let make n =
  let sieve = B.make (n-1) true in
  let primes = V.make () in 
  for i = 2 to n do
    if B.get sieve (i-2) then (
      for k = 2 to n/i do
	B.set sieve (k*i-2) false
      done;
      V.push_back primes i
    )
  done;
  {
    ceiling = n;
    sieve;
    primes
  }

let grow sieve i =
  let n = sieve.ceiling in
  if n < i then (
    let n_new = i in
    B.resize sieve.sieve (n_new-1) true;
    for i = 2 to n do
      if B.get sieve.sieve (i-2) then (
	for k = n/i + 1 to n_new/i do
	  B.set sieve.sieve (k*i-2) false
	done
      )
    done;
    for i = n+1 to n_new do
      if B.get sieve.sieve (i-2) then (
	for k = 2 to n_new/i do
	  B.set sieve.sieve (k*i-2) false
	done;
	V.push_back sieve.primes i
      )
    done;
    sieve.ceiling <- n_new
  )

let grow_to_include sieve i =
  if sieve.ceiling < i then
    grow sieve (max (2*sieve.ceiling) i)

let grow_exponentially sieve =
  grow sieve (2*sieve.ceiling)

let is_prime sieve i =
  if i < 2 then false else (
    grow_to_include sieve i;
    B.get sieve.sieve (i-2)
  )

let get_prime sieve idx =
  while prime_count sieve <= idx do
    grow_exponentially sieve
  done;
  V.get sieve.primes idx

let rec get_prime_after sieve = function
  | n when n < 2 -> 2, 0 (* prime(0) = 2 *)
  | n when n < 3 -> 3, 1 (* prime(1) = 3 *)
  | n -> (
    (* Find a prime greater than n *)
    let rec expsearch x =
      (* PRE: prime(0) < prime(1) <= n
	 POST: n < prime(expsearch(1)) *)
      (* This could probably be improved by having

	 n/ln(n)

	 as an initial guess and then searching from there with
	 
	 n/ln(n) + 2**x

	 but then again, it's probably not worth the effort. *)
      let p = get_prime sieve x in
      if n < p then x else
	expsearch (2*x)
    in
    (* Find the first prime greater than n. *)
    let rec binsearch lx ux =
      (* PRE: prime(lx) <= n && prime(ux) < n *)
      (* POST: prime(binsearch _ _ - 1) <= n && n < prime(binsearch _ _) *)
      if 1 < ux - lx then
	let m  = (lx + ux)/2 in (* INV: ux < m && m < lx *)
	let pm = get_prime sieve m in
	if n < pm then
	  binsearch lx m
	else
	  binsearch m ux
      else
	ux
    in
    (* PRE: prime(1) <= n *)
    let lx = 1 and
	ux = expsearch 2 in
    (* POST: prime(lx) <= n && n < prime(ux) *)
    let x = binsearch lx ux in
    let p = get_prime sieve x in
    (* printf "prime(%d) <= %d && %d < prime(%d)\n" (get_prime sieve (x-1)) n n p; *)
    p, x
  )

let primes_upto sieve i =
  grow_to_include sieve i;
  V.to_array sieve.primes

let prime_factors sieve n =
  let rec consume i rem fl =
    if rem < 2 then
      fl
    else if is_prime sieve rem then
      (* If the remainder is prime,n do not look further *)
      (rem,1)::fl
    else (
      (* Try next prime *)
      let p = get_prime sieve  i in
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
    )
  in
  List.rev (consume 0 n [])

let divisor_count sieve n =
  let pfs = prime_factors sieve n in
  List.fold_left (fun p (_,e) -> p * (e + 1)) 1 pfs

module type S =
  sig
    val get_prime : int -> int
    val get_prime_after : int -> int * index

    val is_prime : int -> bool
    val primes_upto : int -> int array

    val prime_factors : int -> (int * int) list
    val divisor_count : int -> int
  end

module Make (A : sig val initial_size : int end) =
  struct
    let sieve = make A.initial_size

    let get_prime	= get_prime sieve
    let get_prime_after = get_prime_after sieve

    let is_prime	= is_prime sieve
    let primes_upto	= primes_upto sieve

    let prime_factors	= prime_factors sieve
    let divisor_count	= divisor_count sieve
  end

module Default = Make (struct let initial_size = 128 end)
