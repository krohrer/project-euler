open Printf

let coins = [
  200;
  100;
  50;
  20;
  10;
  5;
  2;
  1;
]

let count_change_ways coins cents =
  let rec count sum rem = function
    | _ when rem = 0 -> sum + 1
    | (c::rest) as cs when rem > 0 ->
      (* either take a coin away and continue with all coins *)
      let sum = count sum (rem - c) cs in
      (* or continue with the rest of the coins *)
      count sum rem rest
    | _ -> sum
  in
  count 0 cents coins
  
let _ =
  printf "Solution = %d\n" (count_change_ways coins 200)
