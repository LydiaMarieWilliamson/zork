// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

static Bool thisit(int, int, int, int);

// Find obj described by adj, name pair
// This routine details on bit 3 of prsflg
int getobj(int oidx, int aidx, int spcobj) {
// System generated locals
   int ret_val, i__1;

// Local variables
   int i, av;
   int obj;
   int nobj;
   Bool chomp;

// GETOBJ, PAGE 2

#ifdef ALLOW_GDT
// dflag = (debug.prsflg & 8) != 0; //F
#endif

   chomp = false;
   av = advs.avehic[play.winner - 1];
   obj = 0;
// 						!ASSUME DARK.
   if (!lit(play.here)) {
      goto L200;
   }
// 						!LIT?

   obj = schlst(oidx, aidx, play.here, 0, 0, spcobj);
// 						!SEARCH ROOM.
#ifdef ALLOW_GDT
// if (dflag) print("SCHLST- ROOM SCH %I6", obj); //F
#endif
   if (obj < 0) goto L1000; else if (obj == 0) goto L200;/* else if (obj > 0) goto L100;*/
// 						!TEST RESULT.
L100:
   if (av == 0 || av == obj || (objcts.oflag2[obj - 1] & FindO) != 0) {
      goto L200;
   }
   if (objcts.ocan[obj - 1] == av) {
      goto L200;
   }
// 						!TEST IF REACHABLE.
   chomp = true;
// 						!PROBABLY NOT.

L200:
   if (av == 0) {
      goto L400;
   }
// 						!IN VEHICLE?
   nobj = schlst(oidx, aidx, 0, av, 0, spcobj);
// 						!SEARCH VEHICLE.
#ifdef ALLOW_GDT
// if (dflag) print("SCHLST- VEH SCH  %I6", nobj); //F
#endif
   if (nobj < 0) goto L1100; else if (nobj == 0) goto L400;/* else if (nobj > 0) goto L300;*/
// 						!TEST RESULT.
L300:
   chomp = false;
// 						!REACHABLE.
   if (obj == nobj) {
      goto L400;
   }
// 						!SAME AS BEFORE?
   if (obj != 0) {
      nobj = -nobj;
   }
// 						!AMB RESULT?
   obj = nobj;

L400:
   nobj = schlst(oidx, aidx, 0, 0, play.winner, spcobj);
// 						!SEARCH ADVENTURER.
#ifdef ALLOW_GDT
// if (dflag) print("SCHLST- ADV SCH  %I6", nobj); //F
#endif
   if (nobj < 0) goto L1100; else if (nobj == 0) goto L600;/* else if (nobj > 0) goto L500;*/
// 						!TEST RESULT
L500:
   if (obj != 0) {
      nobj = -nobj;
   }
// 						!AMB RESULT?
L1100:
   obj = nobj;
// 						!RETURN NEW OBJECT.
L600:
   if (chomp) {
      obj = -10000;
   }
// 						!UNREACHABLE.
L1000:
   ret_val = obj;

   if (ret_val != 0) {
      goto L1500;
   }
// 						!GOT SOMETHING?
   i__1 = objcts.olnt;
   for (i = star.strbit + 1; i <= i__1; ++i) {
// 						!NO, SEARCH GLOBALS.
      if (!thisit(oidx, aidx, i, spcobj)) {
         goto L1200;
      }
      if (!ghere(i, play.here)) {
         goto L1200;
      }
// 						!CAN IT BE HERE?
      if (ret_val != 0) {
         ret_val = -i;
      }
// 						!AMB MATCH?
      if (ret_val == 0) {
         ret_val = i;
      }
   L1200:
      ;
   }

L1500:
// 						!END OF SEARCH.
#ifdef ALLOW_GDT
// if (dflag) print("SCHLST- RESULT   %I6", ret_val); //F
#endif
   return ret_val;
}

// Search for object
int schlst(int oidx, int aidx, int rm, int cn, int ad, int spcobj) {
// System generated locals
   int ret_val, i__1, i__2;

// Local variables
   int i, j, x;

   ret_val = 0;
// 						!NO RESULT.
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!SEARCH OBJECTS.
      if ((objcts.oflag1[i - 1] & VisiO) == 0 || (rm == 0 || !qhere(i, rm)) && (cn == 0 || objcts.ocan[i - 1] != cn) && (ad == 0 || objcts.oadv[i - 1] != ad)) {
         goto L1000;
      }
      if (!thisit(oidx, aidx, i, spcobj)) {
         goto L200;
      }
      if (ret_val != 0) {
         goto L2000;
      }
// 						!GOT ONE ALREADY?
      ret_val = i;
// 						!NO.

// IF OPEN OR TRANSPARENT, SEARCH THE OBJECT ITSELF.

   L200:
      if ((objcts.oflag1[i - 1] & TranO) == 0 && (objcts.oflag2[i - 1] & OpenO) == 0) {
         goto L1000;
      }

// SEARCH IS CONDUCTED IN REVERSE.  ALL OBJECTS ARE CHECKED TO
// SEE IF THEY ARE AT SOME LEVEL OF CONTAINMENT INSIDE OBJECT 'I'.
// IF THEY ARE AT LEVEL 1, OR IF ALL LINKS IN THE CONTAINMENT
// CHAIN ARE OPEN, VISIBLE, AND HAVE SEARCHME SET, THEY CAN QUALIFY
// AS A POTENTIAL MATCH.

      i__2 = objcts.olnt;
      for (j = 1; j <= i__2; ++j) {
// 						!SEARCH OBJECTS.
         if ((objcts.oflag1[j - 1] & VisiO) == 0 || !thisit(oidx, aidx, j, spcobj)) {
            goto L500;
         }
         x = objcts.ocan[j - 1];
// 						!GET CONTAINER.
      L300:
         if (x == i) {
            goto L400;
         }
// 						!INSIDE TARGET?
         if (x == 0) {
            goto L500;
         }
// 						!INSIDE ANYTHING?
         if ((objcts.oflag1[x - 1] & VisiO) == 0 || (objcts.oflag1[x - 1] & TranO) == 0 && (objcts.oflag2[x - 1] & OpenO) == 0 || (objcts.oflag2[x - 1] & SchO) == 0) {
            goto L500;
         }
         x = objcts.ocan[x - 1];
// 						!GO ANOTHER LEVEL.
         goto L300;

      L400:
         if (ret_val != 0) {
            goto L2000;
         }
// 						!ALREADY GOT ONE?
         ret_val = j;
// 						!NO.
      L500:
         ;
      }

   L1000:
      ;
   }
   return ret_val;

L2000:
   ret_val = -ret_val;
// 						!AMB RETURN.
   return ret_val;
}

// Validate object versus description
static Bool thisit(int oidx, int aidx, int obj, int spcobj) {
// Initialized data
//    The following data statement used radix-50 notation (r50min/1RA/)
//       In radix-50 notation, an ‟A” in the first position is encoded as 1×40×40 = 1600.
   const int r50min = 1600;

// System generated locals
   Bool ret_val;

// Local variables
   int i;

   ret_val = false;
// 						!ASSUME NO MATCH.
   if (spcobj != 0 && obj == spcobj) {
      goto L500;
   }

// CHECK FOR OBJECT NAMES

   i = oidx + 1;
L100:
   ++i;
   if (ovoc[i - 1] <= 0 || ovoc[i - 1] >= r50min) {
      return ret_val;
   }
// 						!IF DONE, LOSE.
   if (ovoc[i - 1] != obj) {
      goto L100;
   }
// 						!IF FAIL, CONT.

   if (aidx == 0) {
      goto L500;
   }
// 						!ANY ADJ?
   i = aidx + 1;
L200:
   ++i;
   if (avoc[i - 1] <= 0 || avoc[i - 1] >= r50min) {
      return ret_val;
   }
// 						!IF DONE, LOSE.
   if (avoc[i - 1] != obj) {
      goto L200;
   }
// 						!IF FAIL, CONT.

L500:
   ret_val = true;
   return ret_val;
}
