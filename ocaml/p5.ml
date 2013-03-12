open Printf

let _ = 
  let rec search n =
    try
      for i = 1 to 20 do
	if n mod i > 0 then raise Exit
      done;
      printf "Solution = %i" n
    with Exit -> search (n+1)
  in
  search 1
