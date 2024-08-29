require import AllCore IntDiv CoreMap List Distr.
from Jasmin require import JModel_x86.
import SLH64.

from Jasmin require import JLeakage.
require import Array12.
require import WArray48.



module M = {
  var leakages : leakages_t
  
  var assume_sbox1: bool
  var assert_sbox1: bool
  var assume_proof_sbox1: bool
  var assert_proof_sbox1: bool
  
  proc sbox1 (x:W32.t, y:W32.t, z:W32.t) : W32.t = {
    
    
    
    
    assume_sbox1 <- true;
    assert_sbox1 <- true;
    assume_proof_sbox1 <- true;
    assert_proof_sbox1 <- true;
    
    
    return (x);
  }
  
  var assume_sbox2: bool
  var assert_sbox2: bool
  var assume_proof_sbox2: bool
  var assert_proof_sbox2: bool
  
  proc sbox2 (x:W32.t, y:W32.t, z:W32.t) : W32.t = {
    
    
    
    
    assume_sbox2 <- true;
    assert_sbox2 <- true;
    assume_proof_sbox2 <- true;
    assert_proof_sbox2 <- true;
    
    
    return (x);
  }
  
  var assume_sbox3: bool
  var assert_sbox3: bool
  var assume_proof_sbox3: bool
  var assert_proof_sbox3: bool
  
  proc sbox3 (x:W32.t, y:W32.t, z:W32.t) : W32.t = {
    
    
    
    
    assume_sbox3 <- true;
    assert_sbox3 <- true;
    assume_proof_sbox3 <- true;
    assert_proof_sbox3 <- true;
    
    
    return (x);
  }
  
  var assume_sbox: bool
  var assert_sbox: bool
  var assume_proof_sbox: bool
  var assert_proof_sbox: bool
  
  proc sbox (state:W32.t Array12.t, column:W64.t) : W32.t Array12.t = {
    
    
    
    
    assume_sbox <- true;
    assert_sbox <- true;
    assume_proof_sbox <- true;
    assert_proof_sbox <- true;
    
    
    return (state);
  }
  
  var assume_small_swap: bool
  var assert_small_swap: bool
  var assume_proof_small_swap: bool
  var assert_proof_small_swap: bool
  
  proc small_swap (state:W32.t Array12.t) : W32.t Array12.t = {
    
    
    
    
    assume_small_swap <- true;
    assert_small_swap <- true;
    assume_proof_small_swap <- true;
    assert_proof_small_swap <- true;
    
    
    return (state);
  }
  
  var assume_big_swap: bool
  var assert_big_swap: bool
  var assume_proof_big_swap: bool
  var assert_proof_big_swap: bool
  
  proc big_swap (state:W32.t Array12.t) : W32.t Array12.t = {
    
    
    
    
    assume_big_swap <- true;
    assert_big_swap <- true;
    assume_proof_big_swap <- true;
    assert_proof_big_swap <- true;
    
    
    return (state);
  }
  
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
  
  var assume_jazz_sbox1: bool
  var assert_jazz_sbox1: bool
  var assume_proof_jazz_sbox1: bool
  var assert_proof_jazz_sbox1: bool
  
  proc jazz_sbox1 (x:W32.t, y:W32.t, z:W32.t) : W32.t = {
    var aux: W32.t;
    
    var tmp___x: W32.t;
    
    var r:W32.t;
    
    assume_jazz_sbox1 <- true;
    assert_jazz_sbox1 <- true;
    assume_proof_jazz_sbox1 <- true;
    assert_proof_jazz_sbox1 <- true;
    
    leakages <- LeakAddr([]) :: leakages;
    aux <- x;
    x <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <- y;
    y <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <- z;
    z <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <@ sbox1 (x, y, z);
    r <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <- r;
    r <- aux;
    return (r);
  }
  
  var assume_jazz_sbox2: bool
  var assert_jazz_sbox2: bool
  var assume_proof_jazz_sbox2: bool
  var assert_proof_jazz_sbox2: bool
  
  proc jazz_sbox2 (x:W32.t, y:W32.t, z:W32.t) : W32.t = {
    var aux: W32.t;
    
    var tmp___x: W32.t;
    
    var r:W32.t;
    
    assume_jazz_sbox2 <- true;
    assert_jazz_sbox2 <- true;
    assume_proof_jazz_sbox2 <- true;
    assert_proof_jazz_sbox2 <- true;
    
    leakages <- LeakAddr([]) :: leakages;
    aux <- x;
    x <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <- y;
    y <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <- z;
    z <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <@ sbox2 (x, y, z);
    r <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <- r;
    r <- aux;
    return (r);
  }
  
  var assume_jazz_sbox3: bool
  var assert_jazz_sbox3: bool
  var assume_proof_jazz_sbox3: bool
  var assert_proof_jazz_sbox3: bool
  
  proc jazz_sbox3 (x:W32.t, y:W32.t, z:W32.t) : W32.t = {
    var aux: W32.t;
    
    var tmp___x: W32.t;
    
    var r:W32.t;
    
    assume_jazz_sbox3 <- true;
    assert_jazz_sbox3 <- true;
    assume_proof_jazz_sbox3 <- true;
    assert_proof_jazz_sbox3 <- true;
    
    leakages <- LeakAddr([]) :: leakages;
    aux <- x;
    x <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <- y;
    y <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <- z;
    z <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <@ sbox3 (x, y, z);
    r <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <- r;
    r <- aux;
    return (r);
  }
  
  var assume_jazz_sbox: bool
  var assert_jazz_sbox: bool
  var assume_proof_jazz_sbox: bool
  var assert_proof_jazz_sbox: bool
  
  proc jazz_sbox (state:W32.t Array12.t, column:W64.t) : W32.t Array12.t = {
    var aux_0: W64.t;
    var aux: W32.t Array12.t;
    
    var tmp___state: W32.t Array12.t;
    
    
    
    assume_jazz_sbox <- true;
    assert_jazz_sbox <- true;
    assume_proof_jazz_sbox <- true;
    assert_proof_jazz_sbox <- true;
    
    leakages <- LeakAddr([]) :: leakages;
    aux <- state;
    state <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux_0 <- column;
    column <- aux_0;
    leakages <- LeakAddr([]) :: leakages;
    aux <@ sbox (state, column);
    state <- aux;
    return (state);
  }
  
  var assume_jazz_small_swap: bool
  var assert_jazz_small_swap: bool
  var assume_proof_jazz_small_swap: bool
  var assert_proof_jazz_small_swap: bool
  
  proc jazz_small_swap (state:W32.t Array12.t) : W32.t Array12.t = {
    var aux: W32.t Array12.t;
    
    var tmp___state: W32.t Array12.t;
    
    
    
    assume_jazz_small_swap <- true;
    assert_jazz_small_swap <- true;
    assume_proof_jazz_small_swap <- true;
    assert_proof_jazz_small_swap <- true;
    
    leakages <- LeakAddr([]) :: leakages;
    aux <- state;
    state <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <@ small_swap (state);
    state <- aux;
    return (state);
  }
  
  var assume_jazz_big_swap: bool
  var assert_jazz_big_swap: bool
  var assume_proof_jazz_big_swap: bool
  var assert_proof_jazz_big_swap: bool
  
  proc jazz_big_swap (state:W32.t Array12.t) : W32.t Array12.t = {
    var aux: W32.t Array12.t;
    
    var tmp___state: W32.t Array12.t;
    
    
    
    assume_jazz_big_swap <- true;
    assert_jazz_big_swap <- true;
    assume_proof_jazz_big_swap <- true;
    assert_proof_jazz_big_swap <- true;
    
    leakages <- LeakAddr([]) :: leakages;
    aux <- state;
    state <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <@ big_swap (state);
    state <- aux;
    return (state);
  }
  
  var assume_jazz_gimli: bool
  var assert_jazz_gimli: bool
  var assume_proof_jazz_gimli: bool
  var assert_proof_jazz_gimli: bool
  
  proc jazz_gimli (state:W32.t Array12.t) : W32.t Array12.t = {
    var aux: W32.t Array12.t;
    
    var tmp___state: W32.t Array12.t;
    
    
    
    assume_jazz_gimli <- true;
    assert_jazz_gimli <- true;
    assume_proof_jazz_gimli <- true;
    assert_proof_jazz_gimli <- true;
    
    leakages <- LeakAddr([]) :: leakages;
    aux <- state;
    state <- aux;
    leakages <- LeakAddr([]) :: leakages;
    aux <@ gimli (state);
    state <- aux;
    return (state);
  }
}.

axiom sbox1_assert _x _y _z :
  hoare [M.sbox1 :
   (_x = x /\ _y = y /\ _z = z  /\ true)
    ==>
      M.assert_proof_sbox1
      /\
      ((M.assert_sbox1 /\ M.assume_sbox1)
      =>
      (true))
  ].

lemma sbox1_assume :
  hoare [M.sbox1 :
   true
    ==>
      M.assume_proof_sbox1
  ].
proof.
admitted. (*TODO*)

lemma sbox1_assert_assume_sound :
  hoare [M.sbox1 :
   true
    ==>
      (M.assert_proof_sbox1 /\ M.assume_proof_sbox1)
      =>
      (M.assert_sbox1 /\ M.assume_sbox1)
  ].
proof.
admitted. (*TODO*)

lemma sbox1_spec :
  forall _x _y _z,
    hoare [M.sbox1 :
     (_x = x /\ _y = y /\ _z = z  /\ true)
      ==>
        true
    ].
proof.
move =>_x _y _z.
have h: hoare [M.sbox1 :
         (_x = x /\ _y = y /\ _z = z  /\ true)
          ==>
            M.assert_proof_sbox1 /\ M.assume_proof_sbox1
            /\
            ((M.assert_sbox1 /\ M.assume_sbox1)
            =>
            (true))
        ].
+ by conseq sbox1_assume (sbox1_assert _x _y _z).
conseq h sbox1_assert_assume_sound => //; smt().
qed.

axiom sbox2_assert _x _y _z :
  hoare [M.sbox2 :
   (_x = x /\ _y = y /\ _z = z  /\ true)
    ==>
      M.assert_proof_sbox2
      /\
      ((M.assert_sbox2 /\ M.assume_sbox2)
      =>
      (true))
  ].

lemma sbox2_assume :
  hoare [M.sbox2 :
   true
    ==>
      M.assume_proof_sbox2
  ].
proof.
admitted. (*TODO*)

lemma sbox2_assert_assume_sound :
  hoare [M.sbox2 :
   true
    ==>
      (M.assert_proof_sbox2 /\ M.assume_proof_sbox2)
      =>
      (M.assert_sbox2 /\ M.assume_sbox2)
  ].
proof.
admitted. (*TODO*)

lemma sbox2_spec :
  forall _x _y _z,
    hoare [M.sbox2 :
     (_x = x /\ _y = y /\ _z = z  /\ true)
      ==>
        true
    ].
proof.
move =>_x _y _z.
have h: hoare [M.sbox2 :
         (_x = x /\ _y = y /\ _z = z  /\ true)
          ==>
            M.assert_proof_sbox2 /\ M.assume_proof_sbox2
            /\
            ((M.assert_sbox2 /\ M.assume_sbox2)
            =>
            (true))
        ].
+ by conseq sbox2_assume (sbox2_assert _x _y _z).
conseq h sbox2_assert_assume_sound => //; smt().
qed.

axiom sbox3_assert _x _y _z :
  hoare [M.sbox3 :
   (_x = x /\ _y = y /\ _z = z  /\ true)
    ==>
      M.assert_proof_sbox3
      /\
      ((M.assert_sbox3 /\ M.assume_sbox3)
      =>
      (true))
  ].

lemma sbox3_assume :
  hoare [M.sbox3 :
   true
    ==>
      M.assume_proof_sbox3
  ].
proof.
admitted. (*TODO*)

lemma sbox3_assert_assume_sound :
  hoare [M.sbox3 :
   true
    ==>
      (M.assert_proof_sbox3 /\ M.assume_proof_sbox3)
      =>
      (M.assert_sbox3 /\ M.assume_sbox3)
  ].
proof.
admitted. (*TODO*)

lemma sbox3_spec :
  forall _x _y _z,
    hoare [M.sbox3 :
     (_x = x /\ _y = y /\ _z = z  /\ true)
      ==>
        true
    ].
proof.
move =>_x _y _z.
have h: hoare [M.sbox3 :
         (_x = x /\ _y = y /\ _z = z  /\ true)
          ==>
            M.assert_proof_sbox3 /\ M.assume_proof_sbox3
            /\
            ((M.assert_sbox3 /\ M.assume_sbox3)
            =>
            (true))
        ].
+ by conseq sbox3_assume (sbox3_assert _x _y _z).
conseq h sbox3_assert_assume_sound => //; smt().
qed.

axiom sbox_assert _state _column :
  hoare [M.sbox :
   (_state = state /\ _column = column  /\ true)
    ==>
      M.assert_proof_sbox
      /\
      ((M.assert_sbox /\ M.assume_sbox)
      =>
      (true))
  ].

lemma sbox_assume :
  hoare [M.sbox :
   true
    ==>
      M.assume_proof_sbox
  ].
proof.
admitted. (*TODO*)

lemma sbox_assert_assume_sound :
  hoare [M.sbox :
   true
    ==>
      (M.assert_proof_sbox /\ M.assume_proof_sbox)
      =>
      (M.assert_sbox /\ M.assume_sbox)
  ].
proof.
admitted. (*TODO*)

lemma sbox_spec :
  forall _state _column,
    hoare [M.sbox :
     (_state = state /\ _column = column  /\ true)
      ==>
        true
    ].
proof.
move =>_state _column.
have h: hoare [M.sbox :
         (_state = state /\ _column = column  /\ true)
          ==>
            M.assert_proof_sbox /\ M.assume_proof_sbox
            /\
            ((M.assert_sbox /\ M.assume_sbox)
            =>
            (true))
        ].
+ by conseq sbox_assume (sbox_assert _state _column).
conseq h sbox_assert_assume_sound => //; smt().
qed.

axiom small_swap_assert _state :
  hoare [M.small_swap :
   (_state = state  /\ true)
    ==>
      M.assert_proof_small_swap
      /\
      ((M.assert_small_swap /\ M.assume_small_swap)
      =>
      (true))
  ].

lemma small_swap_assume :
  hoare [M.small_swap :
   true
    ==>
      M.assume_proof_small_swap
  ].
proof.
admitted. (*TODO*)

lemma small_swap_assert_assume_sound :
  hoare [M.small_swap :
   true
    ==>
      (M.assert_proof_small_swap /\ M.assume_proof_small_swap)
      =>
      (M.assert_small_swap /\ M.assume_small_swap)
  ].
proof.
admitted. (*TODO*)

lemma small_swap_spec :
  forall _state,
    hoare [M.small_swap :
     (_state = state  /\ true)
      ==>
        true
    ].
proof.
move =>_state.
have h: hoare [M.small_swap :
         (_state = state  /\ true)
          ==>
            M.assert_proof_small_swap /\ M.assume_proof_small_swap
            /\
            ((M.assert_small_swap /\ M.assume_small_swap)
            =>
            (true))
        ].
+ by conseq small_swap_assume (small_swap_assert _state).
conseq h small_swap_assert_assume_sound => //; smt().
qed.

axiom big_swap_assert _state :
  hoare [M.big_swap :
   (_state = state  /\ true)
    ==>
      M.assert_proof_big_swap
      /\
      ((M.assert_big_swap /\ M.assume_big_swap)
      =>
      (true))
  ].

lemma big_swap_assume :
  hoare [M.big_swap :
   true
    ==>
      M.assume_proof_big_swap
  ].
proof.
admitted. (*TODO*)

lemma big_swap_assert_assume_sound :
  hoare [M.big_swap :
   true
    ==>
      (M.assert_proof_big_swap /\ M.assume_proof_big_swap)
      =>
      (M.assert_big_swap /\ M.assume_big_swap)
  ].
proof.
admitted. (*TODO*)

lemma big_swap_spec :
  forall _state,
    hoare [M.big_swap :
     (_state = state  /\ true)
      ==>
        true
    ].
proof.
move =>_state.
have h: hoare [M.big_swap :
         (_state = state  /\ true)
          ==>
            M.assert_proof_big_swap /\ M.assume_proof_big_swap
            /\
            ((M.assert_big_swap /\ M.assume_big_swap)
            =>
            (true))
        ].
+ by conseq big_swap_assume (big_swap_assert _state).
conseq h big_swap_assert_assume_sound => //; smt().
qed.

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

axiom jazz_sbox1_assert _x _y _z :
  hoare [M.jazz_sbox1 :
   (_x = x /\ _y = y /\ _z = z  /\ true)
    ==>
      M.assert_proof_jazz_sbox1
      /\
      ((M.assert_jazz_sbox1 /\ M.assume_jazz_sbox1)
      =>
      (true))
  ].

lemma jazz_sbox1_assume :
  hoare [M.jazz_sbox1 :
   true
    ==>
      M.assume_proof_jazz_sbox1
  ].
proof.
admitted. (*TODO*)

lemma jazz_sbox1_assert_assume_sound :
  hoare [M.jazz_sbox1 :
   true
    ==>
      (M.assert_proof_jazz_sbox1 /\ M.assume_proof_jazz_sbox1)
      =>
      (M.assert_jazz_sbox1 /\ M.assume_jazz_sbox1)
  ].
proof.
admitted. (*TODO*)

lemma jazz_sbox1_spec :
  forall _x _y _z,
    hoare [M.jazz_sbox1 :
     (_x = x /\ _y = y /\ _z = z  /\ true)
      ==>
        true
    ].
proof.
move =>_x _y _z.
have h: hoare [M.jazz_sbox1 :
         (_x = x /\ _y = y /\ _z = z  /\ true)
          ==>
            M.assert_proof_jazz_sbox1 /\ M.assume_proof_jazz_sbox1
            /\
            ((M.assert_jazz_sbox1 /\ M.assume_jazz_sbox1)
            =>
            (true))
        ].
+ by conseq jazz_sbox1_assume (jazz_sbox1_assert _x _y _z).
conseq h jazz_sbox1_assert_assume_sound => //; smt().
qed.

axiom jazz_sbox2_assert _x _y _z :
  hoare [M.jazz_sbox2 :
   (_x = x /\ _y = y /\ _z = z  /\ true)
    ==>
      M.assert_proof_jazz_sbox2
      /\
      ((M.assert_jazz_sbox2 /\ M.assume_jazz_sbox2)
      =>
      (true))
  ].

lemma jazz_sbox2_assume :
  hoare [M.jazz_sbox2 :
   true
    ==>
      M.assume_proof_jazz_sbox2
  ].
proof.
admitted. (*TODO*)

lemma jazz_sbox2_assert_assume_sound :
  hoare [M.jazz_sbox2 :
   true
    ==>
      (M.assert_proof_jazz_sbox2 /\ M.assume_proof_jazz_sbox2)
      =>
      (M.assert_jazz_sbox2 /\ M.assume_jazz_sbox2)
  ].
proof.
admitted. (*TODO*)

lemma jazz_sbox2_spec :
  forall _x _y _z,
    hoare [M.jazz_sbox2 :
     (_x = x /\ _y = y /\ _z = z  /\ true)
      ==>
        true
    ].
proof.
move =>_x _y _z.
have h: hoare [M.jazz_sbox2 :
         (_x = x /\ _y = y /\ _z = z  /\ true)
          ==>
            M.assert_proof_jazz_sbox2 /\ M.assume_proof_jazz_sbox2
            /\
            ((M.assert_jazz_sbox2 /\ M.assume_jazz_sbox2)
            =>
            (true))
        ].
+ by conseq jazz_sbox2_assume (jazz_sbox2_assert _x _y _z).
conseq h jazz_sbox2_assert_assume_sound => //; smt().
qed.

axiom jazz_sbox3_assert _x _y _z :
  hoare [M.jazz_sbox3 :
   (_x = x /\ _y = y /\ _z = z  /\ true)
    ==>
      M.assert_proof_jazz_sbox3
      /\
      ((M.assert_jazz_sbox3 /\ M.assume_jazz_sbox3)
      =>
      (true))
  ].

lemma jazz_sbox3_assume :
  hoare [M.jazz_sbox3 :
   true
    ==>
      M.assume_proof_jazz_sbox3
  ].
proof.
admitted. (*TODO*)

lemma jazz_sbox3_assert_assume_sound :
  hoare [M.jazz_sbox3 :
   true
    ==>
      (M.assert_proof_jazz_sbox3 /\ M.assume_proof_jazz_sbox3)
      =>
      (M.assert_jazz_sbox3 /\ M.assume_jazz_sbox3)
  ].
proof.
admitted. (*TODO*)

lemma jazz_sbox3_spec :
  forall _x _y _z,
    hoare [M.jazz_sbox3 :
     (_x = x /\ _y = y /\ _z = z  /\ true)
      ==>
        true
    ].
proof.
move =>_x _y _z.
have h: hoare [M.jazz_sbox3 :
         (_x = x /\ _y = y /\ _z = z  /\ true)
          ==>
            M.assert_proof_jazz_sbox3 /\ M.assume_proof_jazz_sbox3
            /\
            ((M.assert_jazz_sbox3 /\ M.assume_jazz_sbox3)
            =>
            (true))
        ].
+ by conseq jazz_sbox3_assume (jazz_sbox3_assert _x _y _z).
conseq h jazz_sbox3_assert_assume_sound => //; smt().
qed.

axiom jazz_sbox_assert _state _column :
  hoare [M.jazz_sbox :
   (_state = state /\ _column = column  /\ true)
    ==>
      M.assert_proof_jazz_sbox
      /\
      ((M.assert_jazz_sbox /\ M.assume_jazz_sbox)
      =>
      (true))
  ].

lemma jazz_sbox_assume :
  hoare [M.jazz_sbox :
   true
    ==>
      M.assume_proof_jazz_sbox
  ].
proof.
admitted. (*TODO*)

lemma jazz_sbox_assert_assume_sound :
  hoare [M.jazz_sbox :
   true
    ==>
      (M.assert_proof_jazz_sbox /\ M.assume_proof_jazz_sbox)
      =>
      (M.assert_jazz_sbox /\ M.assume_jazz_sbox)
  ].
proof.
admitted. (*TODO*)

lemma jazz_sbox_spec :
  forall _state _column,
    hoare [M.jazz_sbox :
     (_state = state /\ _column = column  /\ true)
      ==>
        true
    ].
proof.
move =>_state _column.
have h: hoare [M.jazz_sbox :
         (_state = state /\ _column = column  /\ true)
          ==>
            M.assert_proof_jazz_sbox /\ M.assume_proof_jazz_sbox
            /\
            ((M.assert_jazz_sbox /\ M.assume_jazz_sbox)
            =>
            (true))
        ].
+ by conseq jazz_sbox_assume (jazz_sbox_assert _state _column).
conseq h jazz_sbox_assert_assume_sound => //; smt().
qed.

axiom jazz_small_swap_assert _state :
  hoare [M.jazz_small_swap :
   (_state = state  /\ true)
    ==>
      M.assert_proof_jazz_small_swap
      /\
      ((M.assert_jazz_small_swap /\ M.assume_jazz_small_swap)
      =>
      (true))
  ].

lemma jazz_small_swap_assume :
  hoare [M.jazz_small_swap :
   true
    ==>
      M.assume_proof_jazz_small_swap
  ].
proof.
admitted. (*TODO*)

lemma jazz_small_swap_assert_assume_sound :
  hoare [M.jazz_small_swap :
   true
    ==>
      (M.assert_proof_jazz_small_swap /\ M.assume_proof_jazz_small_swap)
      =>
      (M.assert_jazz_small_swap /\ M.assume_jazz_small_swap)
  ].
proof.
admitted. (*TODO*)

lemma jazz_small_swap_spec :
  forall _state,
    hoare [M.jazz_small_swap :
     (_state = state  /\ true)
      ==>
        true
    ].
proof.
move =>_state.
have h: hoare [M.jazz_small_swap :
         (_state = state  /\ true)
          ==>
            M.assert_proof_jazz_small_swap /\ M.assume_proof_jazz_small_swap
            /\
            ((M.assert_jazz_small_swap /\ M.assume_jazz_small_swap)
            =>
            (true))
        ].
+ by conseq jazz_small_swap_assume (jazz_small_swap_assert _state).
conseq h jazz_small_swap_assert_assume_sound => //; smt().
qed.

axiom jazz_big_swap_assert _state :
  hoare [M.jazz_big_swap :
   (_state = state  /\ true)
    ==>
      M.assert_proof_jazz_big_swap
      /\
      ((M.assert_jazz_big_swap /\ M.assume_jazz_big_swap)
      =>
      (true))
  ].

lemma jazz_big_swap_assume :
  hoare [M.jazz_big_swap :
   true
    ==>
      M.assume_proof_jazz_big_swap
  ].
proof.
admitted. (*TODO*)

lemma jazz_big_swap_assert_assume_sound :
  hoare [M.jazz_big_swap :
   true
    ==>
      (M.assert_proof_jazz_big_swap /\ M.assume_proof_jazz_big_swap)
      =>
      (M.assert_jazz_big_swap /\ M.assume_jazz_big_swap)
  ].
proof.
admitted. (*TODO*)

lemma jazz_big_swap_spec :
  forall _state,
    hoare [M.jazz_big_swap :
     (_state = state  /\ true)
      ==>
        true
    ].
proof.
move =>_state.
have h: hoare [M.jazz_big_swap :
         (_state = state  /\ true)
          ==>
            M.assert_proof_jazz_big_swap /\ M.assume_proof_jazz_big_swap
            /\
            ((M.assert_jazz_big_swap /\ M.assume_jazz_big_swap)
            =>
            (true))
        ].
+ by conseq jazz_big_swap_assume (jazz_big_swap_assert _state).
conseq h jazz_big_swap_assert_assume_sound => //; smt().
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