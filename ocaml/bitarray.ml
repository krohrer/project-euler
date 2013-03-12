type t = {
  mutable data : string
}

let make n def = {
  data = String.make n (if def then '\001' else '\000')
}

let length a = String.length a.data

let get s i = s.data.[i] <> '\000'
let set s i b = s.data.[i] <- (if b then '\001' else '\000')

let resize s n def =
  let s_new = make n def in
  String.blit s.data 0 s_new.data 0 (min n (length s));
  s.data <- s_new.data
