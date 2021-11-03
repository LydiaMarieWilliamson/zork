// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

static int unpacks(int);
static int gwim(int, int, int);
static bool syneql(int, int, int, int, int);
static bool takeit(int, int);

// Syntax matcher
// This routine details on bit 4 of prsflg
bool synmch(void) {
// Initialized data
//   The following data statement was originally:
// 	DATA R50MIN/1RA/
   const int r50min = 1600;

// System generated locals
   int i__1;
   bool ret_val;

// Local variables
   int j;
   int newj;
   int drive, limit, qprep, sprep, dforce;

   ret_val = false;
#if defined ALLOW_GDT && 0
   dflag = (debug.prsflg & 16) != 0;
   if (dflag) more_output("synflags=%s%s%s%s%s%s\n", DirS, IndS, StdS, FlipS, DrivS, VMaskS);
#endif
   j = pv.act;
// 						!SET UP PTR TO SYNTAX.
   drive = 0;
// 						!NO DEFAULT.
   dforce = 0;
// 						!NO FORCED DEFAULT.
   qprep = orphs.oflag & orphs.oprep;
L100:
   j += 2;
// 						!FIND START OF SYNTAX.
   if (vvoc[j - 1] <= 0 || vvoc[j - 1] >= r50min) {
      goto L100;
   }
   limit = j + vvoc[j - 1] + 1;
// 						!COMPUTE LIMIT.
   ++j;
// 						!ADVANCE TO NEXT.

L200:
   newj = unpacks(j);
// 						!UNPACK SYNTAX.
#if defined ALLOW_GDT && 0
   if (dflag) more_output("SYNMCH INPUTS TO SYNEQL- %d %d %d %d %d\n", pv.o1, pv.p1, syntax.dobj, syntax.dfl1, syntax.dfl2);
#endif
   sprep = syntax.dobj & PMaskV;
   if (!syneql(pv.p1, pv.o1, syntax.dobj, syntax.dfl1, syntax.dfl2)) {
      goto L1000;
   }
#if defined ALLOW_GDT && 0
   if (dflag) more_output("SYNMCH INPUTS TO SYNEQL- %d %d %d %d %d\n", pv.o2, pv.p2, syntax.iobj, syntax.ifl1, syntax.ifl2);
#endif
   sprep = syntax.iobj & PMaskV;
   if (syneql(pv.p2, pv.o2, syntax.iobj, syntax.ifl1, syntax.ifl2)) {
      goto L6000;
   }

// SYNTAX MATCH FAILS, TRY NEXT ONE.

   if (pv.o2 != 0) {
      goto L3000;
   } else {
      goto L500;
   }
// 						!IF O2=0, SET DFLT.
L1000:
   if (pv.o1 != 0) {
      goto L3000;
   } else {
      goto L500;
   }
// 						!IF O1=0, SET DFLT.
L500:
   if (qprep == 0 || qprep == sprep) {
      dforce = j;
   }
// 						!IF PREP MCH.
   if ((syntax.vflag & DrivS) != 0) {
      drive = j;
   }
L3000:
   j = newj;
   if (j < limit) {
      goto L200;
   }
// 						!MORE TO DO?
// SYNMCH, PAGE 2

// MATCH HAS FAILED.  IF DEFAULT SYNTAX EXISTS, TRY TO SNARF
// ORPHANS OR GWIMS, OR MAKE NEW ORPHANS.

#if defined ALLOW_GDT && 0
   if (dflag) more_output("SYNMCH, DRIVE=%d %d\n", drive, dforce);
#endif
   if (drive == 0) {
      drive = dforce;
   }
// 						!NO DRIVER? USE FORCE.
   if (drive == 0) {
      goto L10000;
   }
// 						!ANY DRIVER?
   dforce = unpacks(drive);
// 						!UNPACK DFLT SYNTAX.

// TRY TO FILL DIRECT OBJECT SLOT IF THAT WAS THE PROBLEM.

   if ((syntax.vflag & DirS) == 0 || pv.o1 != 0) {
      goto L4000;
   }

// FIRST TRY TO SNARF ORPHAN OBJECT.

   pv.o1 = orphs.oflag & orphs.oslot;
   if (pv.o1 == 0) {
      goto L3500;
   }
// 						!ANY ORPHAN?
   if (syneql(pv.p1, pv.o1, syntax.dobj, syntax.dfl1, syntax.dfl2)) {
      goto L4000;
   }

// ORPHAN FAILS, TRY GWIM.

L3500:
   pv.o1 = gwim(syntax.dobj, syntax.dfw1, syntax.dfw2);
// 						!GET GWIM.
#if defined ALLOW_GDT && 0
   if (dflag) more_output("SYNMCH- DO GWIM= %d\n", pv.o1);
#endif
   if (pv.o1 > 0) {
      goto L4000;
   }
// 						!TEST RESULT.
   i__1 = syntax.dobj & PMaskV;
   orphan(-1, pv.act, 0, i__1, 0);
   rspeak(623);
   return ret_val;

// TRY TO FILL INDIRECT OBJECT SLOT IF THAT WAS THE PROBLEM.

L4000:
   if ((syntax.vflag & IndS) == 0 || pv.o2 != 0) {
      goto L6000;
   }
   pv.o2 = gwim(syntax.iobj, syntax.ifw1, syntax.ifw2);
// 						!GWIM.
#if defined ALLOW_GDT && 0
   if (dflag) more_output("SYNMCH- IO GWIM= %d\n", pv.o2);
#endif
   if (pv.o2 > 0) {
      goto L6000;
   }
   if (pv.o1 == 0) {
      pv.o1 = orphs.oflag & orphs.oslot;
   }
   i__1 = syntax.dobj & PMaskV;
   orphan(-1, pv.act, pv.o1, i__1, 0);
   rspeak(624);
   return ret_val;

// TOTAL CHOMP

L10000:
   rspeak(601);
// 						!CANT DO ANYTHING.
   return ret_val;
// SYNMCH, PAGE 3

// NOW TRY TO TAKE INDIVIDUAL OBJECTS AND
// IN GENERAL CLEAN UP THE PARSE VECTOR.

L6000:
   if ((syntax.vflag & FlipS) == 0) {
      goto L5000;
   }
   j = pv.o1;
// 						!YES.
   pv.o1 = pv.o2;
   pv.o2 = j;

L5000:
   prsvec.prsa = syntax.vflag & VMaskS;
   prsvec.prso = pv.o1;
// 						!GET DIR OBJ.
   prsvec.prsi = pv.o2;
// 						!GET IND OBJ.
   if (!takeit(prsvec.prso, syntax.dobj)) {
      return ret_val;
   }
// 						!TRY TAKE.
   if (!takeit(prsvec.prsi, syntax.iobj)) {
      return ret_val;
   }
// 						!TRY TAKE.
   ret_val = true;
#if defined ALLOW_GDT && 0
   if (dflag) more_output("SYNMCH- RESULTS %c %d %d %d %d %d %d\n", ret_val ? 'T' : 'F', prsvec.prsa, prsvec.prso, prsvec.prsi, pv.act, pv.o1, pv.o2);
#endif
   return ret_val;
}

// Unpack syntax specification, adv pointer
static int unpacks(int oldj) {
// Local variables
   int i;

   for (i = 1; i <= 11; ++i) {
// 						!CLEAR SYNTAX.
      syn[i - 1] = 0;
// L10:
   }

   syntax.vflag = vvoc[oldj - 1];
   int j = oldj + 1;
   if ((syntax.vflag & DirS) == 0) {
      return j;
   }
   syntax.dfl1 = -1;
// 						!ASSUME STD.
   syntax.dfl2 = -1;
   if ((syntax.vflag & StdS) == 0) {
      goto L100;
   }
   syntax.dfw1 = -1;
// 						!YES.
   syntax.dfw2 = -1;
   syntax.dobj = AbitV + RbitV + FbitV;
   goto L200;

L100:
   syntax.dobj = vvoc[j - 1];
// 						!NOT STD.
   syntax.dfw1 = vvoc[j];
   syntax.dfw2 = vvoc[j + 1];
   j += 3;
   if ((syntax.dobj & EbitV) == 0) {
      goto L200;
   }
   syntax.dfl1 = syntax.dfw1;
// 						!YES.
   syntax.dfl2 = syntax.dfw2;

L200:
   if ((syntax.vflag & IndS) == 0) {
      return j;
   }
   syntax.ifl1 = -1;
// 						!ASSUME STD.
   syntax.ifl2 = -1;
   syntax.iobj = vvoc[j - 1];
   syntax.ifw1 = vvoc[j];
   syntax.ifw2 = vvoc[j + 1];
   j += 3;
   if ((syntax.iobj & EbitV) == 0) {
      return j;
   }
   syntax.ifl1 = syntax.ifw1;
// 						!YES.
   syntax.ifl2 = syntax.ifw2;
   return j;
}

// Test for syntax equality
static bool syneql(int prep, int obj, int sprep, int sfl1, int sfl2) {
// System generated locals
   bool ret_val;

   if (obj == 0) {
      goto L100;
   }
// 						!ANY OBJECT?
   ret_val = prep == (sprep & PMaskV) && (sfl1 & objcts.oflag1[obj - 1] | sfl2 & objcts.oflag2[obj - 1]) != 0;
   return ret_val;

L100:
   ret_val = prep == 0 && sfl1 == 0 && sfl2 == 0;
   return ret_val;
}

// Parser based take of object
static bool takeit(int obj, int sflag) {
// System generated locals
   bool ret_val;

// Local variables
   int x;
   int odo2;

// TAKEIT, PAGE 2

   ret_val = false;
// 						!ASSUME LOSES.
   if (obj == 0 || obj > star.strbit) {
      goto L4000;
   }
// 						!NULL/STARS WIN.
   odo2 = objcts.odesc2[obj - 1];
// 						!GET DESC.
   x = objcts.ocan[obj - 1];
// 						!GET CONTAINER.
   if (x == 0 || (sflag & FbitV) == 0) {
      goto L500;
   }
   if ((objcts.oflag2[x - 1] & OpenO) != 0) {
      goto L500;
   }
   rspsub(566, odo2);
// 						!CANT REACH.
   return ret_val;

L500:
   if ((sflag & RbitV) == 0) {
      goto L1000;
   }
   if ((sflag & TbitV) == 0) {
      goto L2000;
   }

// SHOULD BE IN ROOM (RbitV NE 0) AND CAN BE TAKEN (TbitV NE 0)

   if (schlst(0, 0, play.here, 0, 0, obj) <= 0) {
      goto L4000;
   }
// 						!IF NOT, OK.

// ITS IN THE ROOM AND CAN BE TAKEN.

   if ((objcts.oflag1[obj - 1] & TakeO) != 0 && (objcts.oflag2[obj - 1] & TryO) == 0) {
      goto L3000;
   }

// NOT TAKEABLE.  IF WE CARE, FAIL.

   if ((sflag & CbitV) == 0) {
      goto L4000;
   }
   rspsub(445, odo2);
   return ret_val;

// 1000--	IT SHOULD NOT BE IN THE ROOM.
// 2000--	IT CANT BE TAKEN.

L2000:
   if ((sflag & CbitV) == 0) {
      goto L4000;
   }
L1000:
   if (schlst(0, 0, play.here, 0, 0, obj) <= 0) {
      goto L4000;
   }
   rspsub(665, odo2);
   return ret_val;
// TAKEIT, PAGE 3

// OBJECT IS IN THE ROOM, CAN BE TAKEN BY THE PARSER,
// AND IS TAKEABLE IN GENERAL.  IT IS NOT A STAR.
// TAKING IT SHOULD NOT HAVE SIDE AFFECTS.
// IF IT IS INSIDE SOMETHING, THE CONTAINER IS OPEN.
// THE FOLLOWING CODE IS LIFTED FROM SUBROUTINE TAKE.

L3000:
   if (obj != advs.avehic[play.winner - 1]) {
      goto L3500;
   }
// 						!TAKE VEHICLE?
   rspeak(672);
   return ret_val;

L3500:
   if (x != 0 && objcts.oadv[x - 1] == play.winner || weight(0, obj, play.winner) + objcts.osize[obj - 1] <= state.mxload) {
      goto L3700;
   }
   rspeak(558);
// 						!TOO BIG.
   return ret_val;

L3700:
   newsta(obj, 559, 0, 0, play.winner);
// 						!DO TAKE.
   objcts.oflag2[obj - 1] |= TChO;
   scrupd(objcts.ofval[obj - 1]);
   objcts.ofval[obj - 1] = 0;

L4000:
   ret_val = true;
// 						!SUCCESS.
   return ret_val;
}

// Get what I mean in ambigous situations
static int gwim(int sflag, int sfw1, int sfw2) {
// System generated locals
   int ret_val;

// Local variables
   int av;
   int nobj, robj;
   bool nocare;

// GWIM, PAGE 2

   ret_val = -1;
// 						!ASSUME LOSE.
   av = advs.avehic[play.winner - 1];
   nobj = 0;
   nocare = (sflag & CbitV) == 0;

// FIRST SEARCH ADVENTURER

   if ((sflag & AbitV) != 0) {
      nobj = fwim(sfw1, sfw2, 0, 0, play.winner, nocare);
   }
   if ((sflag & RbitV) != 0) {
      goto L100;
   }
L50:
   ret_val = nobj;
   return ret_val;

// ALSO SEARCH ROOM

L100:
   robj = fwim(sfw1, sfw2, play.here, 0, 0, nocare);
   if (robj < 0) goto L500; else if (robj == 0) goto L50;/* else if (robj > 0) goto L200; */
// 						!TEST RESULT.

// ROBJ > 0

L200:
   if (av == 0 || robj == av || (objcts.oflag2[robj - 1] & FindO) != 0) {
      goto L300;
   }
   if (objcts.ocan[robj - 1] != av) {
      goto L50;
   }
// 						!UNREACHABLE? TRY NOBJ
L300:
   if (nobj != 0) {
      return ret_val;
   }
// 						!IF AMBIGUOUS, RETURN.
   if (!takeit(robj, sflag)) {
      return ret_val;
   }
// 						!IF UNTAKEABLE, RETURN
   ret_val = robj;
L500:
   return ret_val;
}
