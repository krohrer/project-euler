open Printf

let _ = 
  (* Too lazy to find closed form, but it should be quite easy. *)
  let rec loop ?(sum=0) = function
    | 0 -> sum
    | 1 -> 1 + sum
    | n -> 
      let x = n*n and e = n - 1 in
      loop ~sum:(sum + 4*x - 6*e) (n-2)
  in
  printf "Solution = %d\n" (loop 1001)

