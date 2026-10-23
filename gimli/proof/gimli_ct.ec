require Gimli_x86_ct Gimli_avx_ct.
from Jasmin require import JLeakage.

(** In the CT model, each procedure returns the leakage of its execution in
  * addition to its result. The [state] argument holds a pointer to the data
  * that undergoes the permutation; since it is an address, its value is leaked,
  * and should be public. *)

equiv gimli_x86_ct :
  Gimli_x86_ct.M.gimli ~ Gimli_x86_ct.M.gimli : true ==> res{1}.`1 = res{2}.`1.
proof. proc; inline *; sim: (={leak}). qed.

(*
equiv gimli_avx_ct :
  Gimli_avx_ct.M.gimliv ~ Gimli_avx_ct.M.gimliv : true ==> res{1}.`1 = res{2}.`1.
proof. proc; inline *; sim: (={leak}). qed.
*)
