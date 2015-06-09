open Printf
open Scanf

let _ = 
  let names = 
    let fin = Scanning.open_in "../data/p22.txt" in
    let vec = Vector.make () in
    let rec read_all () =
      try
	bscanf fin "%S" (Vector.push_back vec);
	bscanf fin "," ();
	read_all ()
      with End_of_file -> ()
    in
    read_all ();
    Scanning.close_in fin;
    Vector.to_array vec
  in
  let score s = 
    let sum = ref 0 in
    for i = 0 to String.length s - 1 do
      sum := !sum + Char.code s.[i] - Char.code 'A' + 1
    done;
    !sum
  in
  Array.sort compare names;
  let sum = ref 0 in
  for i = 0 to Array.length names - 1 do
    sum := !sum + (i+1)*score names.(i)
  done;
  printf "Solution = %i\n" !sum
