#use "topfind";;
#require "num";;
open Num

let _ = 
  let p = ref (num_of_int 1) in
  for i = 1 to 100 do
    p := (num_of_int i) */ !p
  done;
  String.length (string_of_num !p)
  
