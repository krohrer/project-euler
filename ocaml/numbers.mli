val gcd : int -> int -> int

val gcd_fold1 : int list -> int

val pow : int -> int -> int

(* factorial for small numbers *)
val fac : int -> int

val digits_fold : ?base:int -> ('a -> int -> 'a) -> 'a -> int -> 'a
