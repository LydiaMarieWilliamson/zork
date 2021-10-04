// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Move player to new room
bool moveto(int nr, int who) {
// System generated locals
   bool ret_val;

// Local variables
   int j;
   bool lhr;
   bool lnr, nlv;
   int bits;

// MOVETO, PAGE 2

   ret_val = false;
// 						!ASSUME FAILS.
   lhr = (rooms.rflag[play.here - 1] & LandR) != 0;
   lnr = (rooms.rflag[nr - 1] & LandR) != 0;
   j = advs.avehic[who - 1];
// 						!HIS VEHICLE

   if (j != 0) {
      goto L100;
   }
// 						!IN VEHICLE?
   if (lnr) {
      goto L500;
   }
// 						!NO, GOING TO LAND?
   rspeak(427);
// 						!CAN'T GO WITHOUT VEHICLE.
   return ret_val;

L100:
   bits = 0;
// 						!ASSUME NOWHERE.
   if (j == RBoatOX) {
      bits = WaterR;
   }
// 						!IN BOAT?
   if (j == BalloOX) {
      bits = AirR;
   }
// 						!IN BALLOON?
   if (j == BuckeOX) {
      bits = BuckR;
   }
// 						!IN BUCKET?
   nlv = (rooms.rflag[nr - 1] & bits) == 0;
   if (!lnr && nlv || lnr && lhr && nlv && bits != LandR) {
      goto L800;
   }

L500:
   ret_val = true;
// 						!MOVE SHOULD SUCCEED.
   if ((rooms.rflag[nr - 1] & MungR) == 0) {
      goto L600;
   }
   rspeak(rrand[nr - 1]);
// 						!YES, TELL HOW.
   return ret_val;

L600:
   if (who != PlayerAX) {
      newsta(advs.aobj[who - 1], 0, nr, 0, 0);
   }
   if (j != 0) {
      newsta(j, 0, nr, 0, 0);
   }
   play.here = nr;
   advs.aroom[who - 1] = play.here;
   scrupd(rooms.rval[nr - 1]);
// 						!SCORE ROOM
   rooms.rval[nr - 1] = 0;
   return ret_val;

L800:
   rspsub(428, objcts.odesc2[j - 1]);
// 						!WRONG VEHICLE.
   return ret_val;
}

// Print out current score
void score(bool flg) {
// Initialized data
   static const int rank[10] = { 20, 19, 18, 16, 12, 8, 4, 2, 1, 0 };
   static const int erank[5] = { 20, 15, 10, 5, 0 };

// System generated locals
   int i__1;

// Local variables
   int i, as;

// SCORE, PAGE 2

   as = advs.ascore[play.winner - 1];

   if (findex_0.endgmf) {
      goto L60;
   }
// 						!ENDGAME?
   more_output("Your score %s %d [total of %d points], in %d %s.\n",
      flg ? "would be" : "is", as, state.mxscor, state.moves, state.moves != 1 ? "moves" : "move"
   );

   for (i = 1; i <= 10; ++i) {
      if (as * 20 / state.mxscor >= rank[i - 1]) {
         goto L50;
      }
// L10:
   }
L50:
   i__1 = i + 484;
   rspeak(i__1);
   return;

L60:
   more_output("Your score in the endgame %s %d [total of %d points], in %d moves.\n",
      flg ? "would be" : "is", state.egscor, state.egmxsc, state.moves
   );
   for (i = 1; i <= 5; ++i) {
      if (state.egscor * 20 / state.egmxsc >= erank[i - 1]) {
         goto L80;
      }
// L70:
   }
L80:
   i__1 = i + 786;
   rspeak(i__1);
}

// Update winner's score
void scrupd(int n) {
   if (findex_0.endgmf) {
      goto L100;
   }
// 						!ENDGAME?
   advs.ascore[play.winner - 1] += n;
// 						!UPDATE SCORE
   state.rwscor += n;
// 						!UPDATE RAW SCORE
   if (advs.ascore[play.winner - 1] < state.mxscor - state.deaths * 10) {
      return;
   }
   cevent.cflag[EghCX - 1] = true;
// 						!TURN ON END GAME
   cevent.ctick[EghCX - 1] = 15;
   return;

L100:
   state.egscor += n;
// 						!UPDATE EG SCORE.
}
