#use "topfind";;
#require "num";;

open Num
open Printf

let _ = 
  let digits = string_of_num (num_of_int 2 **/ num_of_int 1000) in
  let n = String.length digits in
  let sum = ref 0 in
  for i = 0 to n-1 do
    sum := !sum + (Char.code digits.[i] - Char.code '0')
  done;
  printf "Solution = %d\n" !sum
