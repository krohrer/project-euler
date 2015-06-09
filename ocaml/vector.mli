type 'a t

val make : ?capacity:int -> unit -> 'a t

val count : 'a t -> int
val capacity : 'a t -> int

val is_empty : 'a t -> bool

val push_back : 'a t -> 'a -> unit
val pop_back : 'a t -> 'a

val reserve : 'a t -> int -> unit
val resize : 'a t -> int -> 'a -> unit

val get : 'a t -> int -> 'a
val set : 'a t -> int -> 'a -> unit

val safe_get : 'a t -> int -> 'a -> 'a

val to_array : 'a t -> 'a array
val to_list : 'a t -> 'a list

val fold_left  : ('a -> 'b -> 'a) -> 'a -> 'b t -> 'a
val fold_right : ('a -> 'b -> 'b) -> 'a t -> 'b -> 'b
