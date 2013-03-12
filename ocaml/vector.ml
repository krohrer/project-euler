type 'a t = {
  mutable count : int;
  mutable data : Obj.t array;
}

let make ?(capacity=8) () =
  {
    count = 0;
    data = Array.create capacity (Obj.repr 0)
  }

let capacity v =
  Array.length v.data

let count v =
  v.count

let insert_last v e =
  let cap = capacity v in
  let i = v.count in
  if cap <= i then begin
    let data = Array.create (2*cap) (Obj.repr 0) in
    Array.blit v.data 0 data 0 v.count;
    v.data <- data
  end;
  v.data.(v.count) <- Obj.repr e;
  v.count <- v.count + 1
  
let get v i =
  assert (i < v.count);
  Obj.obj v.data.(i)

let set v i e = 
  v.data.(i) <- Obj.repr e

let to_array v =
  Array.init v.count (fun i -> Obj.obj v.data.(i))
