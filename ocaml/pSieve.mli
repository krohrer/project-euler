type t

val make : int -> t

val ceiling : t -> int

val prime_count : t -> int
val get_prime : t -> int -> int

val is_prime : t -> int -> bool
val primes : t -> int -> int array

val prime_factors : t -> int -> (int * int) list
val divisor_count : t -> int -> int
