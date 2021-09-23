// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Basic take sequence
// Take an object (for verbs take, put, drop, read, etc.)
Bool take(Bool flg) {
// System generated locals
   int i__1;
   Bool ret_val;

// Local variables
   int x, oa;

// TAKE, PAGE 2

   ret_val = false;
// 						!ASSUME LOSES.
   oa = objcts_1.oactio[prsvec_1.prso - 1];
// 						!GET OBJECT ACTION.
   if (prsvec_1.prso <= star_1.strbit) {
      goto L100;
   }
// 						!STAR?
   ret_val = objact(/*x*/);
// 						!YES, LET IT HANDLE.
   return ret_val;

L100:
   x = objcts_1.ocan[prsvec_1.prso - 1];
// 						!INSIDE?
   if (prsvec_1.prso != advs_1.avehic[play_1.winner - 1]) {
      goto L400;
   }
// 						!HIS VEHICLE?
   rspeak(672);
// 						!DUMMY.
   return ret_val;

L400:
   if ((objcts_1.oflag1[prsvec_1.prso - 1] & TakeO) != 0) {
      goto L500;
   }
   if (!oappli(oa, 0)) {
      i__1 = rnd(5) + 552;
      rspeak(i__1);
   }
   return ret_val;

// OBJECT IS TAKEABLE AND IN POSITION TO BE TAKEN.

L500:
   if (x != 0 || qhere(prsvec_1.prso, play_1.here)) {
      goto L600;
   }
   if (objcts_1.oadv[prsvec_1.prso - 1] == play_1.winner) {
      rspeak(557);
   }
// 						!ALREADY GOT IT?
   return ret_val;

L600:
   if (x != 0 && objcts_1.oadv[x - 1] == play_1.winner || weight(0, prsvec_1.prso, play_1.winner) + objcts_1.osize[prsvec_1.prso - 1] <= state_1.mxload) {
      goto L700;
   }
   rspeak(558);
// 						!TOO MUCH WEIGHT.
   return ret_val;

L700:
   ret_val = true;
// 						!AT LAST.
   if (oappli(oa, 0)) {
      return ret_val;
   }
// 						!DID IT HANDLE?
   newsta(prsvec_1.prso, 0, 0, 0, play_1.winner);
// 						!TAKE OBJECT FOR WINNER.
   objcts_1.oflag2[prsvec_1.prso - 1] |= TChO;
   scrupd(objcts_1.ofval[prsvec_1.prso - 1]);
// 						!UPDATE SCORE.
   objcts_1.ofval[prsvec_1.prso - 1] = 0;
// 						!CANT BE SCORED AGAIN.
   if (flg) {
      rspeak(559);
   }
// 						!TELL TAKEN.
   return ret_val;
}

// Drop verb processor
Bool drop(/*Bool z*/) {
// System generated locals
   Bool ret_val;

// Local variables
   Bool f;
   int i, x;

// DROP, PAGE 2

   ret_val = true;
// 						!ASSUME WINS.
   x = objcts_1.ocan[prsvec_1.prso - 1];
// 						!GET CONTAINER.
   if (x == 0) {
      goto L200;
   }
// 						!IS IT INSIDE?
   if (objcts_1.oadv[x - 1] != play_1.winner) {
      goto L1000;
   }
// 						!IS HE CARRYING CON?
   if ((objcts_1.oflag2[x - 1] & OpenO) != 0) {
      goto L300;
   }
   rspsub(525, objcts_1.odesc2[x - 1]);
// 						!CANT REACH.
   return ret_val;

L200:
   if (objcts_1.oadv[prsvec_1.prso - 1] != play_1.winner) {
      goto L1000;
   }
// 						!IS HE CARRYING OBJ?
L300:
   if (advs_1.avehic[play_1.winner - 1] == 0) {
      goto L400;
   }
// 						!IS HE IN VEHICLE?
   prsvec_1.prsi = advs_1.avehic[play_1.winner - 1];
// 						!YES,
   f = put(/*true*/);
// 						!DROP INTO VEHICLE.
   prsvec_1.prsi = 0;
// 						!DISARM PARSER.
   return ret_val;
// 						!DONE.

L400:
   newsta(prsvec_1.prso, 0, play_1.here, 0, 0);
// 						!DROP INTO ROOM.
   if (play_1.here == rindex_1.mtree) {
      newsta(prsvec_1.prso, 0, rindex_1.fore3, 0, 0);
   }
   scrupd(objcts_1.ofval[prsvec_1.prso - 1]);
// 						!SCORE OBJECT.
   objcts_1.ofval[prsvec_1.prso - 1] = 0;
// 						!CANT BE SCORED AGAIN.
   objcts_1.oflag2[prsvec_1.prso - 1] |= TChO;

   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!DID IT HANDLE?
   i = 0;
// 						!ASSUME NOTHING TO SAY.
   if (prsvec_1.prsa == vindex_1.dropw) {
      i = 528;
   }
   if (prsvec_1.prsa == vindex_1.throww) {
      i = 529;
   }
   if (i != 0 && play_1.here == rindex_1.mtree) {
      i = 659;
   }
   rspsub(i, objcts_1.odesc2[prsvec_1.prso - 1]);
   return ret_val;

L1000:
   rspeak(527);
// 						!DONT HAVE IT.
   return ret_val;
}

// Put verb processor
Bool put(/*Bool flg*/) {
// System generated locals
   Bool ret_val;

// Local variables
   int j;
#if 0
   int x; //(@) No longer used.
#endif
   int svi, svo;

// PUT, PAGE 2

   ret_val = false;
   if (prsvec_1.prso <= star_1.strbit && prsvec_1.prsi <= star_1.strbit) {
      goto L200;
   }
   if (!objact(/*x*/)) {
      rspeak(560);
   }
// 						!STAR
   ret_val = true;
   return ret_val;

L200:
   if ((objcts_1.oflag2[prsvec_1.prsi - 1] & OpenO) != 0 || (objcts_1.oflag1[prsvec_1.prsi - 1] & DoorO + ContO) != 0 || (objcts_1.oflag2[prsvec_1.prsi - 1] & VehO) != 0) {
      goto L300;
   }
   rspeak(561);
// 						!CANT PUT IN THAT.
   return ret_val;

L300:
   if ((objcts_1.oflag2[prsvec_1.prsi - 1] & OpenO) != 0) {
      goto L400;
   }
// 						!IS IT OPEN?
   rspeak(562);
// 						!NO, JOKE
   return ret_val;

L400:
   if (prsvec_1.prso != prsvec_1.prsi) {
      goto L500;
   }
// 						!INTO ITSELF?
   rspeak(563);
// 						!YES, JOKE.
   return ret_val;

L500:
   if (objcts_1.ocan[prsvec_1.prso - 1] != prsvec_1.prsi) {
      goto L600;
   }
// 						!ALREADY INSIDE.
   rspsb2(564, objcts_1.odesc2[prsvec_1.prso - 1], objcts_1.odesc2[prsvec_1.prsi - 1]);
   ret_val = true;
   return ret_val;

L600:
   if (weight(0, prsvec_1.prso, 0) + weight(0, prsvec_1.prsi, 0) + objcts_1.osize[prsvec_1.prso - 1] <= objcts_1.ocapac[prsvec_1.prsi - 1]) {
      goto L700;
   }
   rspeak(565);
// 						!THEN CANT DO IT.
   return ret_val;

// NOW SEE IF OBJECT (OR ITS CONTAINER) IS IN ROOM

L700:
   j = prsvec_1.prso;
// 						!START SEARCH.
L725:
   if (qhere(j, play_1.here)) {
      goto L750;
   }
// 						!IS IT HERE?
   j = objcts_1.ocan[j - 1];
   if (j != 0) {
      goto L725;
   }
// 						!MORE TO DO?
   goto L800;
// 						!NO, SCH FAILS.

L750:
   svo = prsvec_1.prso;
// 						!SAVE PARSER.
   svi = prsvec_1.prsi;
   prsvec_1.prsa = vindex_1.takew;
   prsvec_1.prsi = 0;
   if (!take(false)) {
      return ret_val;
   }
// 						!TAKE OBJECT.
   prsvec_1.prsa = vindex_1.putw;
   prsvec_1.prso = svo;
   prsvec_1.prsi = svi;
   goto L1000;

// NOW SEE IF OBJECT IS ON PERSON.

L800:
   if (objcts_1.ocan[prsvec_1.prso - 1] == 0) {
      goto L1000;
   }
// 						!INSIDE?
   if ((objcts_1.oflag2[objcts_1.ocan[prsvec_1.prso - 1] - 1] & OpenO) != 0) {
      goto L900;
   }
// 						!OPEN?
   rspsub(566, objcts_1.odesc2[prsvec_1.prso - 1]);
// 						!LOSE.
   return ret_val;

L900:
   scrupd(objcts_1.ofval[prsvec_1.prso - 1]);
// 						!SCORE OBJECT.
   objcts_1.ofval[prsvec_1.prso - 1] = 0;
   objcts_1.oflag2[prsvec_1.prso - 1] |= TChO;
   newsta(prsvec_1.prso, 0, 0, 0, play_1.winner);
// 						!TEMPORARILY ON WINNER.

L1000:
   if (objact(/*x*/)) {
      return ret_val;
   }
// 						!NO, GIVE OBJECT A SHOT.
   newsta(prsvec_1.prso, 2, 0, prsvec_1.prsi, 0);
// 						!CONTAINED INSIDE.
   ret_val = true;
   return ret_val;
}

// Handles valuables/everything
void valuac(int v) {
// System generated locals
   int i__1;

// Local variables
   Bool f;
   int i;
   Bool f1;
   int savep, saveh;

// VALUAC, PAGE 2

   f = true;
// 						!ASSUME NO ACTIONS.
   i = 579;
// 						!ASSUME NOT LIT.
   if (!lit(play_1.here)) {
      goto L4000;
   }
// 						!IF NOT LIT, PUNT.
   i = 677;
// 						!ASSUME WRONG VERB.
   savep = prsvec_1.prso;
// 						!SAVE PRSO.
   saveh = play_1.here;
// 						!SAVE HERE.

//L100:
   if (prsvec_1.prsa != vindex_1.takew) {
      goto L1000;
   }
// 						!TAKE EVERY/VALUA?
   i__1 = objcts_1.olnt;
   for (prsvec_1.prso = 1; prsvec_1.prso <= i__1; ++prsvec_1.prso) {
// 						!LOOP THRU OBJECTS.
      if (!qhere(prsvec_1.prso, play_1.here) || (objcts_1.oflag1[prsvec_1.prso - 1] & VisiO) == 0 || (objcts_1.oflag2[prsvec_1.prso - 1] & ActrO) != 0 || savep == v && objcts_1.otval[prsvec_1.prso - 1] <= 0) {
         goto L500;
      }
      if ((objcts_1.oflag1[prsvec_1.prso - 1] & TakeO) == 0 && (objcts_1.oflag2[prsvec_1.prso - 1] & TryO) == 0) {
         goto L500;
      }
      f = false;
      rspsub(580, objcts_1.odesc2[prsvec_1.prso - 1]);
      f1 = take(true);
      if (saveh != play_1.here) {
         return;
      }
   L500:
      ;
   }
   goto L3000;

L1000:
   if (prsvec_1.prsa != vindex_1.dropw) {
      goto L2000;
   }
// 						!DROP EVERY/VALUA?
   i__1 = objcts_1.olnt;
   for (prsvec_1.prso = 1; prsvec_1.prso <= i__1; ++prsvec_1.prso) {
      if (objcts_1.oadv[prsvec_1.prso - 1] != play_1.winner || savep == v && objcts_1.otval[prsvec_1.prso - 1] <= 0) {
         goto L1500;
      }
      f = false;
      rspsub(580, objcts_1.odesc2[prsvec_1.prso - 1]);
      f1 = drop(/*true*/);
      if (saveh != play_1.here) {
         return;
      }
   L1500:
      ;
   }
   goto L3000;

L2000:
   if (prsvec_1.prsa != vindex_1.putw) {
      goto L3000;
   }
// 						!PUT EVERY/VALUA?
   i__1 = objcts_1.olnt;
   for (prsvec_1.prso = 1; prsvec_1.prso <= i__1; ++prsvec_1.prso) {
// 						!LOOP THRU OBJECTS.
      if (objcts_1.oadv[prsvec_1.prso - 1] != play_1.winner || prsvec_1.prso == prsvec_1.prsi || savep == v && objcts_1.otval[prsvec_1.prso - 1] <= 0 || (objcts_1.oflag1[prsvec_1.prso - 1] & VisiO) == 0) {
         goto L2500;
      }
      f = false;
      rspsub(580, objcts_1.odesc2[prsvec_1.prso - 1]);
      f1 = put(/*true*/);
      if (saveh != play_1.here) {
         return;
      }
   L2500:
      ;
   }

L3000:
   i = 581;
   if (savep == v) {
      i = 582;
   }
// 						!CHOOSE MESSAGE.
L4000:
   if (f) {
      rspeak(i);
   }
// 						!IF NOTHING, REPORT.
}
