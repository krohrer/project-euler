type t
type index = int

val make : int -> t

val ceiling : t -> int
val prime_count : t -> int

val get_prime : t -> index -> int
val get_prime_after : t -> int -> int * index

val is_prime : t -> int -> bool
val primes_upto : t -> int -> int array

val prime_factors : t -> int -> (int * int) list
val divisor_count : t -> int -> int

module type S =
  sig
    val get_prime : index -> int
    val get_prime_after : int -> int * index

    val is_prime : int -> bool
    val primes_upto : int -> int array

    val prime_factors : int -> (int * int) list
    val divisor_count : int -> int
  end

module Make (A : sig val initial_size : int end) : S
module Default : S
