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

let is_empty v =
  v.count == 0

let reserve' v n zr =
  let cap = capacity v in
  if cap <= n then begin
    let cap = max (2*cap) n in
    let data = Array.create (2*cap) zr in
    Array.blit v.data 0 data 0 v.count;
    v.data <- data
  end

let resize v n z =
  reserve' v n (Obj.repr z);
  v.count <- n

let reserve v n =
  reserve' v n (Obj.repr 0)

let push_back v e =
  let c = v.count + 1 in
  reserve v c;
  v.data.(v.count) <- Obj.repr e;
  v.count <- c

let pop_back v =
  assert (0 < v.count);
  let i = v.count - 1 in
  let e = Obj.obj v.data.(i) in
  v.count <- i;
  e
  
let get v i =
  assert (i < v.count);
  Obj.obj v.data.(i)

let set v i e = 
  v.data.(i) <- Obj.repr e

let to_array v =
  Array.init v.count (fun i -> Obj.obj v.data.(i))

let to_list v =
  let rec loop a l = function
    | i when i < 0	-> l
    | i			-> let l = Obj.obj a.(i) :: l in
			   loop a l (i-1)
  in
  loop v.data [] (v.count-1)

let fold_left f z v =
  let rec loop f z a n = function
    | i when i < n	-> let z = f z (Obj.obj a.(i)) in
			   loop f z a n (i+1)
    | i			-> z
  in
  loop f z v.data v.count 0

let fold_right f v z =
  let rec loop f a z = function
    | i when i < 0	-> z
    | i			-> let z = f (Obj.obj a.(i)) z in
			   loop f a z (i-1)
  in
  loop f v.data z (v.count-1)

let safe_get v i z =
  if 0 <= i && i < v.count then
    get v i
  else
    z

