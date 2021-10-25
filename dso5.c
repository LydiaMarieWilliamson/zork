// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Get total time played
long gttime(void) {
   return time2001() - time_.stime + time_.pltime;
}

// Process open/close for doors
bool opncls(int obj, int so, int sc) {
// System generated locals
   int i__1;
   bool ret_val;

   ret_val = true;
// 						!ASSUME WINS.
   if (prsvec.prsa == CloseW) {
      goto L100;
   }
// 						!CLOSE?
   if (prsvec.prsa == OpenW) {
      goto L50;
   }
// 						!OPEN?
   ret_val = false;
// 						!LOSE
   return ret_val;

L50:
   if ((objcts.oflag2[obj - 1] & OpenO) != 0) {
      goto L200;
   }
// 						!OPEN... IS IT?
   rspeak(so);
   objcts.oflag2[obj - 1] |= OpenO;
   return ret_val;

L100:
   if (!((objcts.oflag2[obj - 1] & OpenO) != 0)) {
      goto L200;
   }
// 						!CLOSE... IS IT?
   rspeak(sc);
   objcts.oflag2[obj - 1] &= ~OpenO;
   return ret_val;

L200:
   i__1 = rnd(3) + 125;
   rspeak(i__1);
// 						!DUMMY.
   return ret_val;
}

// Is room lit?
bool lit(int rm) {
// System generated locals
   int i__1, i__2;
   bool ret_val;

// Local variables
   int i, j, oa;

   ret_val = true;
// 						!ASSUME WINS
   if ((rooms.rflag[rm - 1] & LightR) != 0) {
      return ret_val;
   }

   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!LOOK FOR LIT OBJ
      if (qhere(i, rm)) {
         goto L100;
      }
// 						!IN ROOM?
      oa = objcts.oadv[i - 1];
// 						!NO
      if (oa <= 0) {
         goto L1000;
      }
// 						!ON ADV?
      if (advs.aroom[oa - 1] != rm) {
         goto L1000;
      }
// 						!ADV IN ROOM?

// OBJ IN ROOM OR ON ADV IN ROOM

   L100:
      if ((objcts.oflag1[i - 1] & OnO) != 0) {
         return ret_val;
      }
      if ((objcts.oflag1[i - 1] & VisiO) == 0 || (objcts.oflag1[i - 1] & TranO) == 0 && (objcts.oflag2[i - 1] & OpenO) == 0) {
         goto L1000;
      }

// OBJ IS VISIBLE AND OPEN OR TRANSPARENT

      i__2 = objcts.olnt;
      for (j = 1; j <= i__2; ++j) {
         if (objcts.ocan[j - 1] == i && (objcts.oflag1[j - 1] & OnO) != 0) {
            return ret_val;
         }
   // L500:
      }
   L1000:
      ;
   }
   ret_val = false;
   return ret_val;
}

// Returns sum of weight of qualifying objects
int weight(int rm, int cn, int ad) {
// System generated locals
   int ret_val, i__1;

// Local variables
   int i, j;

   ret_val = 0;
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!OMIT BIG FIXED ITEMS.
      if (objcts.osize[i - 1] >= 10000) {
         goto L100;
      }
// 						!IF FIXED, FORGET IT.
      if (qhere(i, rm) && rm != 0 || objcts.oadv[i - 1] == ad && ad != 0) {
         goto L50;
      }
      j = i;
// 						!SEE IF CONTAINED.
   L25:
      j = objcts.ocan[j - 1];
// 						!GET NEXT LEVEL UP.
      if (j == 0) {
         goto L100;
      }
// 						!END OF LIST?
      if (j != cn) {
         goto L25;
      }
   L50:
      ret_val += objcts.osize[i - 1];
   L100:
      ;
   }
   return ret_val;
}
