open Printf

let recuring_cycle denom =
  let lut = Array.create denom (-1) in
  let rec divide idx = function
    | 0 ->
      0
    | rem when 0 < lut.(rem-1) ->
      idx - lut.(rem-1)
    | rem ->
      lut.(rem-1) <- idx;
      let num = 10 * rem in
      let _ = num / denom and
	  rem' = num mod denom in
      divide (idx+1) rem'
  in
  lut.(0) <- 0;
  divide 0 1

let _ =
  let cyc_max = ref 0 and
      i_max = ref 0 in
  for i = 1 to 1000 do
    let cyc = recuring_cycle i in
    (*
    printf "1/%d = %.20f: longest cycle: %d\n"
      i (1. /. float_of_int i) cyc;*)
    if cyc > !cyc_max then begin
      cyc_max := cyc;
      i_max := i
    end
  done;
  printf "Solution = %d" !i_max
