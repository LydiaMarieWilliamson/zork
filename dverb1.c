// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Basic take sequence
// Take an object (for verbs take, put, drop, read, etc.)
bool take(bool flg) {
// System generated locals
   int i__1;
   bool ret_val;

// Local variables
   int x, oa;

// TAKE, PAGE 2

   ret_val = false;
// 						!ASSUME LOSES.
   oa = objcts.oactio[prsvec.prso - 1];
// 						!GET OBJECT ACTION.
   if (prsvec.prso <= star.strbit) {
      goto L100;
   }
// 						!STAR?
   ret_val = objact();
// 						!YES, LET IT HANDLE.
   return ret_val;

L100:
   x = objcts.ocan[prsvec.prso - 1];
// 						!INSIDE?
   if (prsvec.prso != advs.avehic[play.winner - 1]) {
      goto L400;
   }
// 						!HIS VEHICLE?
   rspeak(672);
// 						!DUMMY.
   return ret_val;

L400:
   if ((objcts.oflag1[prsvec.prso - 1] & TakeO) != 0) {
      goto L500;
   }
   if (!oappli(oa, 0)) {
      i__1 = rnd(5) + 552;
      rspeak(i__1);
   }
   return ret_val;

// OBJECT IS TAKEABLE AND IN POSITION TO BE TAKEN.

L500:
   if (x != 0 || qhere(prsvec.prso, play.here)) {
      goto L600;
   }
   if (objcts.oadv[prsvec.prso - 1] == play.winner) {
      rspeak(557);
   }
// 						!ALREADY GOT IT?
   return ret_val;

L600:
   if (x != 0 && objcts.oadv[x - 1] == play.winner || weight(0, prsvec.prso, play.winner) + objcts.osize[prsvec.prso - 1] <= state.mxload) {
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
   newsta(prsvec.prso, 0, 0, 0, play.winner);
// 						!TAKE OBJECT FOR WINNER.
   objcts.oflag2[prsvec.prso - 1] |= TChO;
   scrupd(objcts.ofval[prsvec.prso - 1]);
// 						!UPDATE SCORE.
   objcts.ofval[prsvec.prso - 1] = 0;
// 						!CANT BE SCORED AGAIN.
   if (flg) {
      rspeak(559);
   }
// 						!TELL TAKEN.
   return ret_val;
}

// Drop verb processor
bool drop(void) {
// System generated locals
   bool ret_val;

// Local variables
   bool f;
   int i, x;

// DROP, PAGE 2

   ret_val = true;
// 						!ASSUME WINS.
   x = objcts.ocan[prsvec.prso - 1];
// 						!GET CONTAINER.
   if (x == 0) {
      goto L200;
   }
// 						!IS IT INSIDE?
   if (objcts.oadv[x - 1] != play.winner) {
      goto L1000;
   }
// 						!IS HE CARRYING CON?
   if ((objcts.oflag2[x - 1] & OpenO) != 0) {
      goto L300;
   }
   rspsub(525, objcts.odesc2[x - 1]);
// 						!CANT REACH.
   return ret_val;

L200:
   if (objcts.oadv[prsvec.prso - 1] != play.winner) {
      goto L1000;
   }
// 						!IS HE CARRYING OBJ?
L300:
   if (advs.avehic[play.winner - 1] == 0) {
      goto L400;
   }
// 						!IS HE IN VEHICLE?
   prsvec.prsi = advs.avehic[play.winner - 1];
// 						!YES,
   f = put();
// 						!DROP INTO VEHICLE.
   prsvec.prsi = 0;
// 						!DISARM PARSER.
   return ret_val;
// 						!DONE.

L400:
   newsta(prsvec.prso, 0, play.here, 0, 0);
// 						!DROP INTO ROOM.
   if (play.here == MTreeRX) {
      newsta(prsvec.prso, 0, Fore3RX, 0, 0);
   }
   scrupd(objcts.ofval[prsvec.prso - 1]);
// 						!SCORE OBJECT.
   objcts.ofval[prsvec.prso - 1] = 0;
// 						!CANT BE SCORED AGAIN.
   objcts.oflag2[prsvec.prso - 1] |= TChO;

   if (objact()) {
      return ret_val;
   }
// 						!DID IT HANDLE?
   i = 0;
// 						!ASSUME NOTHING TO SAY.
   if (prsvec.prsa == DropW) {
      i = 528;
   }
   if (prsvec.prsa == ThrowW) {
      i = 529;
   }
   if (i != 0 && play.here == MTreeRX) {
      i = 659;
   }
   rspsub(i, objcts.odesc2[prsvec.prso - 1]);
   return ret_val;

L1000:
   rspeak(527);
// 						!DONT HAVE IT.
   return ret_val;
}

// Put verb processor
bool put(void) {
// System generated locals
   bool ret_val;

// Local variables
   int j;
#if 0
   int x; //(@) No longer used.
#endif
   int svi, svo;

// PUT, PAGE 2

   ret_val = false;
   if (prsvec.prso <= star.strbit && prsvec.prsi <= star.strbit) {
      goto L200;
   }
   if (!objact()) {
      rspeak(560);
   }
// 						!STAR
   ret_val = true;
   return ret_val;

L200:
   if ((objcts.oflag2[prsvec.prsi - 1] & OpenO) != 0 || (objcts.oflag1[prsvec.prsi - 1] & DoorO + ContO) != 0 || (objcts.oflag2[prsvec.prsi - 1] & VehO) != 0) {
      goto L300;
   }
   rspeak(561);
// 						!CANT PUT IN THAT.
   return ret_val;

L300:
   if ((objcts.oflag2[prsvec.prsi - 1] & OpenO) != 0) {
      goto L400;
   }
// 						!IS IT OPEN?
   rspeak(562);
// 						!NO, JOKE
   return ret_val;

L400:
   if (prsvec.prso != prsvec.prsi) {
      goto L500;
   }
// 						!INTO ITSELF?
   rspeak(563);
// 						!YES, JOKE.
   return ret_val;

L500:
   if (objcts.ocan[prsvec.prso - 1] != prsvec.prsi) {
      goto L600;
   }
// 						!ALREADY INSIDE.
   rspsb2(564, objcts.odesc2[prsvec.prso - 1], objcts.odesc2[prsvec.prsi - 1]);
   ret_val = true;
   return ret_val;

L600:
   if (weight(0, prsvec.prso, 0) + weight(0, prsvec.prsi, 0) + objcts.osize[prsvec.prso - 1] <= objcts.ocapac[prsvec.prsi - 1]) {
      goto L700;
   }
   rspeak(565);
// 						!THEN CANT DO IT.
   return ret_val;

// NOW SEE IF OBJECT (OR ITS CONTAINER) IS IN ROOM

L700:
   j = prsvec.prso;
// 						!START SEARCH.
L725:
   if (qhere(j, play.here)) {
      goto L750;
   }
// 						!IS IT HERE?
   j = objcts.ocan[j - 1];
   if (j != 0) {
      goto L725;
   }
// 						!MORE TO DO?
   goto L800;
// 						!NO, SCH FAILS.

L750:
   svo = prsvec.prso;
// 						!SAVE PARSER.
   svi = prsvec.prsi;
   prsvec.prsa = TakeW;
   prsvec.prsi = 0;
   if (!take(false)) {
      return ret_val;
   }
// 						!TAKE OBJECT.
   prsvec.prsa = PutW;
   prsvec.prso = svo;
   prsvec.prsi = svi;
   goto L1000;

// NOW SEE IF OBJECT IS ON PERSON.

L800:
   if (objcts.ocan[prsvec.prso - 1] == 0) {
      goto L1000;
   }
// 						!INSIDE?
   if ((objcts.oflag2[objcts.ocan[prsvec.prso - 1] - 1] & OpenO) != 0) {
      goto L900;
   }
// 						!OPEN?
   rspsub(566, objcts.odesc2[prsvec.prso - 1]);
// 						!LOSE.
   return ret_val;

L900:
   scrupd(objcts.ofval[prsvec.prso - 1]);
// 						!SCORE OBJECT.
   objcts.ofval[prsvec.prso - 1] = 0;
   objcts.oflag2[prsvec.prso - 1] |= TChO;
   newsta(prsvec.prso, 0, 0, 0, play.winner);
// 						!TEMPORARILY ON WINNER.

L1000:
   if (objact()) {
      return ret_val;
   }
// 						!NO, GIVE OBJECT A SHOT.
   newsta(prsvec.prso, 2, 0, prsvec.prsi, 0);
// 						!CONTAINED INSIDE.
   ret_val = true;
   return ret_val;
}

// Handles valuables/everything
void valuac(int v) {
// System generated locals
   int i__1;

// Local variables
   bool f;
   int i;
   bool f1;
   int savep, saveh;

// VALUAC, PAGE 2

   f = true;
// 						!ASSUME NO ACTIONS.
   i = 579;
// 						!ASSUME NOT LIT.
   if (!lit(play.here)) {
      goto L4000;
   }
// 						!IF NOT LIT, PUNT.
   i = 677;
// 						!ASSUME WRONG VERB.
   savep = prsvec.prso;
// 						!SAVE PRSO.
   saveh = play.here;
// 						!SAVE HERE.

//L100:
   if (prsvec.prsa != TakeW) {
      goto L1000;
   }
// 						!TAKE EVERY/VALUA?
   i__1 = objcts.olnt;
   for (prsvec.prso = 1; prsvec.prso <= i__1; ++prsvec.prso) {
// 						!LOOP THRU OBJECTS.
      if (!qhere(prsvec.prso, play.here) || (objcts.oflag1[prsvec.prso - 1] & VisiO) == 0 || (objcts.oflag2[prsvec.prso - 1] & ActrO) != 0 || savep == v && objcts.otval[prsvec.prso - 1] <= 0) {
         goto L500;
      }
      if ((objcts.oflag1[prsvec.prso - 1] & TakeO) == 0 && (objcts.oflag2[prsvec.prso - 1] & TryO) == 0) {
         goto L500;
      }
      f = false;
      rspsub(580, objcts.odesc2[prsvec.prso - 1]);
      f1 = take(true);
      if (saveh != play.here) {
         return;
      }
   L500:
      ;
   }
   goto L3000;

L1000:
   if (prsvec.prsa != DropW) {
      goto L2000;
   }
// 						!DROP EVERY/VALUA?
   i__1 = objcts.olnt;
   for (prsvec.prso = 1; prsvec.prso <= i__1; ++prsvec.prso) {
      if (objcts.oadv[prsvec.prso - 1] != play.winner || savep == v && objcts.otval[prsvec.prso - 1] <= 0) {
         goto L1500;
      }
      f = false;
      rspsub(580, objcts.odesc2[prsvec.prso - 1]);
      f1 = drop();
      if (saveh != play.here) {
         return;
      }
   L1500:
      ;
   }
   goto L3000;

L2000:
   if (prsvec.prsa != PutW) {
      goto L3000;
   }
// 						!PUT EVERY/VALUA?
   i__1 = objcts.olnt;
   for (prsvec.prso = 1; prsvec.prso <= i__1; ++prsvec.prso) {
// 						!LOOP THRU OBJECTS.
      if (objcts.oadv[prsvec.prso - 1] != play.winner || prsvec.prso == prsvec.prsi || savep == v && objcts.otval[prsvec.prso - 1] <= 0 || (objcts.oflag1[prsvec.prso - 1] & VisiO) == 0) {
         goto L2500;
      }
      f = false;
      rspsub(580, objcts.odesc2[prsvec.prso - 1]);
      f1 = put();
      if (saveh != play.here) {
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
