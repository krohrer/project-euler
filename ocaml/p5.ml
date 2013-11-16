open Printf

let _ = 
  let rec search n =
    try
      for i = 18 downto 1 do
	if n mod i > 0 then raise Exit
      done;
      printf "Solution = %i" n
    with Exit -> search (n+20*19)
  in
  search (20*19)
