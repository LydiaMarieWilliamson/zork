// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include <stdio.h>
#include "extern.h"
#include "common.h"

// Move player to new room
Bool moveto(int nr, int who) {
// System generated locals
   Bool ret_val;

// Local variables
   int j;
   Bool lhr;
   Bool lnr, nlv;
   int bits;

   ret_val = false;
// 						!ASSUME FAILS.
   lhr = (rooms_1.rflag[play_1.here - 1] & LandR) != 0;
   lnr = (rooms_1.rflag[nr - 1] & LandR) != 0;
   j = advs_1.avehic[who - 1];
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
   if (j == oindex_1.rboat) {
      bits = WaterR;
   }
// 						!IN BOAT?
   if (j == oindex_1.ballo) {
      bits = AirR;
   }
// 						!IN BALLOON?
   if (j == oindex_1.bucke) {
      bits = BuckR;
   }
// 						!IN BUCKET?
   nlv = (rooms_1.rflag[nr - 1] & bits) == 0;
   if (!lnr && nlv || lnr && lhr && nlv && bits != LandR) {
      goto L800;
   }

L500:
   ret_val = true;
// 						!MOVE SHOULD SUCCEED.
   if ((rooms_1.rflag[nr - 1] & MungR) == 0) {
      goto L600;
   }
   rspeak(rrand[nr - 1]);
// 						!YES, TELL HOW.
   return ret_val;

L600:
   if (who != aindex_1.player) {
      newsta(advs_1.aobj[who - 1], 0, nr, 0, 0);
   }
   if (j != 0) {
      newsta(j, 0, nr, 0, 0);
   }
   play_1.here = nr;
   advs_1.aroom[who - 1] = play_1.here;
   scrupd(rooms_1.rval[nr - 1]);
// 						!SCORE ROOM
   rooms_1.rval[nr - 1] = 0;
   return ret_val;

L800:
   rspsub(428, objcts_1.odesc2[j - 1]);
// 						!WRONG VEHICLE.
   return ret_val;
}

// Print out current score
void score(Bool flg) {
// Initialized data
   static const int rank[10] = { 20, 19, 18, 16, 12, 8, 4, 2, 1, 0 };
   static const int erank[5] = { 20, 15, 10, 5, 0 };

// System generated locals
   int i__1;

// Local variables
   int i, as;

   as = advs_1.ascore[play_1.winner - 1];

   if (findex_1.endgmf) {
      goto L60;
   }
// 						!ENDGAME?
// if (flg) //F
//    write(chan_1.outch, " Your score would be%$"); //F
// else //F
//    write(chan_1.outch, " Your score is%$"); //F
   more_output(NULL), printf("Your score ");
   if (flg) printf("would be"); else printf("is");
// if (state_1.moves != 1) //F
//    write(chan_1.outch, "%I4 [total of%I4 points], in%I5 moves."); //F
// else //F
//    write(chan_1.outch, "%I4 [total of%I4 points], in%I5 move."); //F
   printf(" %d [total of %d points], in %d ", as, state_1.mxscor, state_1.moves);
   if (state_1.moves != 1) printf("moves"); else printf("move");
   printf(".\n");

   for (i = 1; i <= 10; ++i) {
      if (as * 20 / state_1.mxscor >= rank[i - 1]) {
         goto L50;
      }
// L10:
   }
L50:
   i__1 = i + 484;
   rspeak(i__1);
   return;

L60:
// if (flg)
//    write(chan_1.outch, " Your score in the endgame would be%$"); //F
// else
//    write(chan_1.outch, " Your score in the endgame is%$"); //F
   more_output(NULL), printf("Your score in the endgame ");
   if (flg) printf("would be"); else printf("is");
// write(chan_1.outch, "%I4 [total of%I4 points], in%I5 moves.", //F
//    state_1.egscor, state_1.egmxsc, state_1.moves //F
// ); //F
   printf(" %d [total of %d points], in %d moves.\n", state_1.egscor, state_1.egmxsc, state_1.moves);

   for (i = 1; i <= 5; ++i) {
      if (state_1.egscor * 20 / state_1.egmxsc >= erank[i - 1]) {
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
   if (findex_1.endgmf) {
      goto L100;
   }
// 						!ENDGAME?
   advs_1.ascore[play_1.winner - 1] += n;
// 						!UPDATE SCORE
   state_1.rwscor += n;
// 						!UPDATE RAW SCORE
   if (advs_1.ascore[play_1.winner - 1] < state_1.mxscor - state_1.deaths * 10) {
      return;
   }
   cevent_1.cflag[cindex_1.cevegh - 1] = true;
// 						!TURN ON END GAME
   cevent_1.ctick[cindex_1.cevegh - 1] = 15;
   return;

L100:
   state_1.egscor += n;
// 						!UPDATE EG SCORE.
}
