type t

val make : int -> t

val cutoff : t -> int

val is_prime : t -> int -> bool
val primes : t -> int -> int array
