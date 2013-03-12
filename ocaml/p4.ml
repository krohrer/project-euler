open Printf

let is_palindrome s =
  let n = String.length s in
  let rec check i k =
    i >= k || (s.[i] = s.[k] && check (i+1) (k-1))
  in
  check 0 (n-1)

let _ =
  let max = ref 0 in
  for i = 999 downto 100 do
    for k = 999 downto 100 do
      let p = i*k in
      if is_palindrome (string_of_int p) && p > !max then max := p
    done
  done;
  printf "Solution = %i\n" !max
