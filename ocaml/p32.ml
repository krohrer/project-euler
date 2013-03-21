open Printf

let digits = [|1;2;3;4;5;6;7;8;9|]

let array_swap a i k =
  let t = a.(i) in
  a.(i) <- a.(k); a.(k) <- t

let rec array_extract_digits a i = function
  | n when n > 0 -> 
    (10 * array_extract_digits a i (n-1)) + a.(i+n-1)
  | _ -> 0

let permute_iter f a =
  let n = Array.length a in
  let rec loop = function
    | r when r > 1 ->
      let i = n-r in
      for k = i to n-1 do
	array_swap a i k;
	loop (r-1);
	array_swap a i k
      done
    | _ -> f a
  in
  loop n

let _ =  
  let sum = ref 0 in
  permute_iter (fun _ -> sum := !sum + 1) [|1;2;3;4;5;6;7;8;9|];
  !sum
