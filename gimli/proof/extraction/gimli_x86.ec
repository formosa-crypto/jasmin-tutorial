require import AllCore IntDiv CoreMap List Distr.
from Jasmin require import JModel_x86.
import SLH64.


require import Array12.
require import WArray48.



module M = {
  var assume_gimli: bool
  var assert_gimli: bool
  var assume_proof_gimli: bool
  var assert_proof_gimli: bool
  
  proc gimli (state:W32.t Array12.t) : W32.t Array12.t = {
    
    
    
    
    assume_gimli <- true;
    assert_gimli <- true;
    assume_proof_gimli <- true;
    assert_proof_gimli <- true;
    
    
    return (state);
  }
  
  var assume_jazz_gimli: bool
  var assert_jazz_gimli: bool
  var assume_proof_jazz_gimli: bool
  var assert_proof_jazz_gimli: bool
  
  proc jazz_gimli (state:W32.t Array12.t) : W32.t Array12.t = {
    
    var tmp___state: W32.t Array12.t;
    
    
    
    assume_jazz_gimli <- true;
    assert_jazz_gimli <- true;
    assume_proof_jazz_gimli <- true;
    assert_proof_jazz_gimli <- true;
    
    state <- state;
    
    tmp___state <@ gimli (state);
    
    state <- tmp___state;
    
    return (state);
  }
}.

axiom gimli_assert _state :
  hoare [M.gimli :
   (_state = state  /\ true)
    ==>
      M.assert_proof_gimli
      /\
      ((M.assert_gimli /\ M.assume_gimli)
      =>
      (true))
  ].

lemma gimli_assume :
  hoare [M.gimli :
   true
    ==>
      M.assume_proof_gimli
  ].
proof.
admitted. (*TODO*)

lemma gimli_assert_assume_sound :
  hoare [M.gimli :
   true
    ==>
      (M.assert_proof_gimli /\ M.assume_proof_gimli)
      =>
      (M.assert_gimli /\ M.assume_gimli)
  ].
proof.
admitted. (*TODO*)

lemma gimli_spec :
  forall _state,
    hoare [M.gimli :
     (_state = state  /\ true)
      ==>
        true
    ].
proof.
move =>_state.
have h: hoare [M.gimli :
         (_state = state  /\ true)
          ==>
            M.assert_proof_gimli /\ M.assume_proof_gimli
            /\
            ((M.assert_gimli /\ M.assume_gimli)
            =>
            (true))
        ].
+ by conseq gimli_assume (gimli_assert _state).
conseq h gimli_assert_assume_sound => //; smt().
qed.

axiom jazz_gimli_assert _state :
  hoare [M.jazz_gimli :
   (_state = state  /\ true)
    ==>
      M.assert_proof_jazz_gimli
      /\
      ((M.assert_jazz_gimli /\ M.assume_jazz_gimli)
      =>
      (true))
  ].

lemma jazz_gimli_assume :
  hoare [M.jazz_gimli :
   true
    ==>
      M.assume_proof_jazz_gimli
  ].
proof.
admitted. (*TODO*)

lemma jazz_gimli_assert_assume_sound :
  hoare [M.jazz_gimli :
   true
    ==>
      (M.assert_proof_jazz_gimli /\ M.assume_proof_jazz_gimli)
      =>
      (M.assert_jazz_gimli /\ M.assume_jazz_gimli)
  ].
proof.
admitted. (*TODO*)

lemma jazz_gimli_spec :
  forall _state,
    hoare [M.jazz_gimli :
     (_state = state  /\ true)
      ==>
        true
    ].
proof.
move =>_state.
have h: hoare [M.jazz_gimli :
         (_state = state  /\ true)
          ==>
            M.assert_proof_jazz_gimli /\ M.assume_proof_jazz_gimli
            /\
            ((M.assert_jazz_gimli /\ M.assume_jazz_gimli)
            =>
            (true))
        ].
+ by conseq jazz_gimli_assume (jazz_gimli_assert _state).
conseq h jazz_gimli_assert_assume_sound => //; smt().