type t
  
val make : int -> bool -> t
val length : t -> int

val set : t -> int -> bool -> unit
val get : t -> int -> bool

val resize : t -> int -> bool -> unit

val fold_left : f:('a -> bool -> 'a) -> 'a -> t -> 'a
val count_ones : t -> int
