type 'a t = {
  mutable count : int;
  mutable data : Obj.t array;
}

let make ?(cap=8) () =
  {
    count = 0;
    data = Array.create cap (Obj.repr 0)
  }

let capacity v =
  Array.length v.data

let count v =
  v.count

let insert_last v e =
  let cap = capacity v in
  let i = count in
  if cap <= i then begin
    let data = Array.create (2*cap) (Obj.repr 0) in
    Array.blit v.data 0 data 0 count;
    v.data <- data
  end;
  v.data.(count) <- e;
  v.count <- v.count + 1
  
let get v i =
  Obj.obj v.data.(i)

let set v i e = 
  v.data.(i) <- Obj.repr e
