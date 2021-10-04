// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Steal winner's valuables
int robadv(int adv, int nr, int nc, int na) {
// System generated locals
   int ret_val, i__1;

// Local variables
   int i;

   ret_val = 0;
// 						!COUNT OBJECTS
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
      if (objcts.oadv[i - 1] != adv || objcts.otval[i - 1] <= 0 || (objcts.oflag2[i - 1] & ScrDO) != 0) {
         goto L100;
      }
      newsta(i, 0, nr, nc, na);
// 						!STEAL OBJECT
      ++ret_val;
   L100:
      ;
   }
   return ret_val;
}

// Steal room valuables
int robrm(int rm, int pr, int nr, int nc, int na) {
// System generated locals
   int ret_val, i__1, i__2;

// Local variables
   int i;

   ret_val = 0;
// 						!COUNT OBJECTS
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!LOOP ON OBJECTS.
      if (!qhere(i, rm)) {
         goto L100;
      }
      if (objcts.otval[i - 1] <= 0 || (objcts.oflag2[i - 1] & ScrDO) != 0 || (objcts.oflag1[i - 1] & VisiO) == 0 || !prob(pr, pr)) {
         goto L50;
      }
      newsta(i, 0, nr, nc, na);
      ++ret_val;
      objcts.oflag2[i - 1] |= TChO;
      goto L100;
   L50:
      if ((objcts.oflag2[i - 1] & ActrO) != 0) {
         i__2 = oactor(i);
         ret_val += robadv(i__2, nr, nc, na);
      }
   L100:
      ;
   }
   return ret_val;
}

// See if villain is winning
bool winnin(int vl, int hr) {
// System generated locals
   bool ret_val;

// Local variables
   int ps, vs;

   vs = objcts.ocapac[vl - 1];
// 						!VILLAIN STRENGTH
   ps = vs - fights(hr, true);
// 						!HIS MARGIN OVER HERO
   ret_val = prob(90, 100);
   if (ps > 3) {
      return ret_val;
   }
// 						!+3... 90% WINNING
   ret_val = prob(75, 85);
   if (ps > 0) {
      return ret_val;
   }
// 						!>0... 75% WINNING
   ret_val = prob(50, 30);
   if (ps == 0) {
      return ret_val;
   }
// 						!=0... 50% WINNING
   ret_val = prob(25, 25);
   if (vs > 1) {
      return ret_val;
   }
// 						!ANY VILLAIN STRENGTH.
   ret_val = prob(10, 0);
   return ret_val;
}

// Compute fight strength
int fights(int h, bool flg) {
// Initialized data
   const int smin = 2;
   const int smax = 7;

// System generated locals
   int ret_val;

   ret_val = smin + ((smax - smin) * advs.ascore[h - 1] + state.mxscor / 2) / state.mxscor;
   if (flg) {
      ret_val += advs.astren[h - 1];
   }
   return ret_val;
}

// Compute villain strength
int vilstr(int v) {
// System generated locals
   int ret_val, i__1, i__2, i__3;

// Local variables
   int i;

// VILSTR, PAGE 2

   ret_val = objcts.ocapac[v - 1];
   if (ret_val <= 0) {
      return ret_val;
   }
   if (v != ThiefOX || !findex_0.thfenf) {
      goto L100;
   }
   findex_0.thfenf = false;
// 						!THIEF UNENGROSSED.
   ret_val = min(ret_val, 2);
// 						!NO BETTER THAN 2.

L100:
   i__1 = vill.vlnt;
   for (i = 1; i <= i__1; ++i) {
// 						!SEE IF  BEST WEAPON.
      if (vill.villns[i - 1] == v && prsvec.prsi == vill.vbest[i - 1]) {
// Computing MAX
         i__2 = 1, i__3 = ret_val - 1;
         ret_val = max(i__2, i__3);
      }
// L200:
   }
   return ret_val;
}
