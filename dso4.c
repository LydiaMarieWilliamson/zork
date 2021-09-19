// ROBADV-- STEAL WINNER'S VALUABLES

// COPYRIGHT 1980, INFOCOM COMPUTERS AND COMMUNICATIONS, CAMBRIDGE MA. 02142
// ALL RIGHTS RESERVED, COMMERCIAL USAGE STRICTLY PROHIBITED
// WRITTEN BY R. M. SUPNIK

#include "extern.h"
#include "common.h"

int robadv_(int adv, int nr, int nc, int na) {
// System generated locals
   int ret_val, i__1;

// Local variables
   int i;

   ret_val = 0;
// 						!COUNT OBJECTS
   i__1 = objcts_1.olnt;
   for (i = 1; i <= i__1; ++i) {
      if (objcts_1.oadv[i - 1] != adv || objcts_1.otval[i - 1] <= 0 || (objcts_1.oflag2[i - 1] & ScrDO) != 0) {
         goto L100;
      }
      newsta_(i, 0, nr, nc, na);
// 						!STEAL OBJECT
      ++ret_val;
   L100:
      ;
   }
   return ret_val;
}

// ROBRM-- STEAL ROOM VALUABLES

int robrm_(int rm, int pr, int nr, int nc, int na) {
// System generated locals
   int ret_val, i__1, i__2;

// Local variables
   int i;

// OBJECTS

   ret_val = 0;
// 						!COUNT OBJECTS
   i__1 = objcts_1.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!LOOP ON OBJECTS.
      if (!qhere_(i, rm)) {
         goto L100;
      }
      if (objcts_1.otval[i - 1] <= 0 || (objcts_1.oflag2[i - 1] & ScrDO) != 0 || (objcts_1.oflag1[i - 1] & VisiO) == 0 || !prob_(pr, pr)) {
         goto L50;
      }
      newsta_(i, 0, nr, nc, na);
      ++ret_val;
      objcts_1.oflag2[i - 1] |= TChO;
      goto L100;
   L50:
      if ((objcts_1.oflag2[i - 1] & ActrO) != 0) {
         i__2 = oactor_(i);
         ret_val += robadv_(i__2, nr, nc, na);
      }
   L100:
      ;
   }
   return ret_val;
}

// WINNIN-- SEE IF VILLAIN IS WINNING

Bool winnin_(int vl, int hr) {
// System generated locals
   Bool ret_val;

// Local variables
   int ps, vs;

// OBJECTS

   vs = objcts_1.ocapac[vl - 1];
// 						!VILLAIN STRENGTH
   ps = vs - fights_(hr, true);
// 						!HIS MARGIN OVER HERO
   ret_val = prob_(90, 100);
   if (ps > 3) {
      return ret_val;
   }
// 						!+3... 90% WINNING
   ret_val = prob_(75, 85);
   if (ps > 0) {
      return ret_val;
   }
// 						!>0... 75% WINNING
   ret_val = prob_(50, 30);
   if (ps == 0) {
      return ret_val;
   }
// 						!=0... 50% WINNING
   ret_val = prob_(25, 25);
   if (vs > 1) {
      return ret_val;
   }
// 						!ANY VILLAIN STRENGTH.
   ret_val = prob_(10, 0);
   return ret_val;
}

// FIGHTS-- COMPUTE FIGHT STRENGTH

int fights_(int h, Bool flg) {
// Initialized data
   const int smin = 2;
   const int smax = 7;

// System generated locals
   int ret_val;

   ret_val = smin + ((smax - smin) * advs_1.ascore[h - 1] + state_1.mxscor / 2) / state_1.mxscor;
   if (flg) {
      ret_val += advs_1.astren[h - 1];
   }
   return ret_val;
}

// VILSTR-	COMPUTE VILLAIN STRENGTH

int vilstr_(int v) {
// System generated locals
   int ret_val, i__1, i__2, i__3;

// Local variables
   int i;

   ret_val = objcts_1.ocapac[v - 1];
   if (ret_val <= 0) {
      return ret_val;
   }
   if (v != oindex_1.thief || !findex_1.thfenf) {
      goto L100;
   }
   findex_1.thfenf = false;
// 						!THIEF UNENGROSSED.
   ret_val = min(ret_val, 2);
// 						!NO BETTER THAN 2.

L100:
   i__1 = vill_1.vlnt;
   for (i = 1; i <= i__1; ++i) {
// 						!SEE IF  BEST WEAPON.
      if (vill_1.villns[i - 1] == v && prsvec_1.prsi == vill_1.vbest[i - 1]) {
// Computing MAX
         i__2 = 1, i__3 = ret_val - 1;
         ret_val = max(i__2, i__3);
      }
// L200:
   }
   return ret_val;
}
