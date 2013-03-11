type 'a t

val make : ?capacity:int -> unit -> 'a t

val count : 'a t -> int
val capacity : 'a t -> int

val insert_last : 'a t -> 'a -> unit

val get : 'a t -> int -> 'a
val set : 'a t -> int -> 'a -> unit
