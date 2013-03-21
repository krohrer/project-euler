open Printf

let p29_brute_force n = 
  (* Brute force for once *)
  let module S =
	Set.Make(struct
	  type t = Num.num
	  let compare = Num.compare_num
	end)
  in
  let s = ref S.empty in
  for a = 2 to n do
    for b = 2 to n do
      s := S.add Num.(Int a **/ Int b) !s
    done
  done;
  S.cardinal !s

let p29_canonical n =
  (* Slightly cleverer *)
  let module P = PSieve.Default in
  let canonical_form a b = 
    let pfactors = P.prime_factors a in
    let pexps = List.map snd pfactors in
    match Numbers.gcd_fold1 pexps with
    | 1 -> a + (n+1)*b
    | d ->
      let a' = int_of_float ((float a) ** (1. /. float d)) and
	  b' = b * d in
      a' + (n+1)*b'
  in
  let module S =
	Set.Make(struct
	  type t = int
	  let compare = compare
	end)
  in
  let canonicals = ref S.empty in
  let count_canonicals () = S.cardinal !canonicals in
  let add_form a b =
    canonicals := S.add (canonical_form a b) !canonicals
  in
  for a = 2 to n do
    for b = 2 to n do
      add_form a b
    done
  done;
  count_canonicals ()

let p29_canonical_ht n =
  (* Slightly cleverer, with hashtable *)
  let module P = PSieve.Default in
  let canonical_form a b = 
    let pfactors = P.prime_factors a in
    let pexps = List.map snd pfactors in
    match Numbers.gcd_fold1 pexps with
    | 1 -> a + (n+1)*b
    | d ->
      let a' = int_of_float ((float a) ** (1. /. float d)) and
	  b' = b * d in
      a' + (n+1)*b'
  in
  let canonicals = Hashtbl.create (n*n) in
  let count_canonicals () = Hashtbl.length canonicals in
  let add_form a b =
    Hashtbl.replace canonicals (canonical_form a b) ()
  in
  for a = 2 to n do
    for b = 2 to n do
      add_form a b
    done
  done;
  count_canonicals ()

let _ =
  let n = 100 in
  let meth = `Table in
  let calc =
    match meth with
    | `Brute -> p29_brute_force
    | `Set   -> p29_canonical
    | `Table -> p29_canonical_ht
  in
  printf "Solution = %d\n" (calc n)
