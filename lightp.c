// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Light processor
Bool lightp(int obj) {
// System generated locals
   Bool ret_val;

// Local variables
   int flobts;
   int i;

// LIGHTP, PAGE 2

   ret_val = true;
// 						!ASSUME WINS
   flobts = FlamO + LiteO + OnO;
   if (obj != oindex_1.candl) {
      goto L20000;
   }
// 						!CANDLE?
   if (findex_1.orcand != 0) {
      goto L19100;
   }
// 						!FIRST REF?
   findex_1.orcand = 1;
// 						!YES, CANDLES ARE
   cevent_1.ctick[cindex_1.cevcnd - 1] = 50;
// 						!BURNING WHEN SEEN.

L19100:
   if (prsvec_1.prsi == oindex_1.candl) {
      goto L10;
   }
// 						!IGNORE IND REFS.
   if (prsvec_1.prsa != vindex_1.trnofw) {
      goto L19200;
   }
// 						!TURN OFF?
   i = 513;
// 						!ASSUME OFF.
   if ((objcts_1.oflag1[oindex_1.candl - 1] & OnO) != 0) {
      i = 514;
   }
// 						!IF ON, DIFFERENT.
   cevent_1.cflag[cindex_1.cevcnd - 1] = false;
// 						!DISABLE COUNTDOWN.
   objcts_1.oflag1[oindex_1.candl - 1] &= ~OnO;
   rspeak(i);
   return ret_val;

L19200:
   if (prsvec_1.prsa != vindex_1.burnw && prsvec_1.prsa != vindex_1.trnonw) {
      goto L10;
   }
   if ((objcts_1.oflag1[oindex_1.candl - 1] & LiteO) != 0) {
      goto L19300;
   }
   rspeak(515);
// 						!CANDLES TOO SHORT.
   return ret_val;

L19300:
   if (prsvec_1.prsi != 0) {
      goto L19400;
   }
// 						!ANY FLAME?
   rspeak(516);
// 						!NO, LOSE.
   prsvec_1.prswon = false;
   return ret_val;

L19400:
   if (prsvec_1.prsi != oindex_1.match || !((objcts_1.oflag1[oindex_1.match - 1] & OnO) != 0)) {
      goto L19500;
   }
   i = 517;
// 						!ASSUME OFF.
   if ((objcts_1.oflag1[oindex_1.candl - 1] & OnO) != 0) {
      i = 518;
   }
// 						!IF ON, JOKE.
   objcts_1.oflag1[oindex_1.candl - 1] |= OnO;
   cevent_1.cflag[cindex_1.cevcnd - 1] = true;
// 						!RESUME COUNTDOWN.
   rspeak(i);
   return ret_val;

L19500:
   if (prsvec_1.prsi != oindex_1.torch || !((objcts_1.oflag1[oindex_1.torch - 1] & OnO) != 0)) {
      goto L19600;
   }
   if ((objcts_1.oflag1[oindex_1.candl - 1] & OnO) != 0) {
      goto L19700;
   }
// 						!ALREADY ON?
   newsta(oindex_1.candl, 521, 0, 0, 0);
// 						!NO, VAPORIZE.
   return ret_val;

L19600:
   rspeak(519);
// 						!CANT LIGHT WITH THAT.
   return ret_val;

L19700:
   rspeak(520);
// 						!ALREADY ON.
   return ret_val;

L20000:
   if (obj != oindex_1.match) {
      bug(6, obj);
   }
   if (prsvec_1.prsa != vindex_1.trnonw || prsvec_1.prso != oindex_1.match) {
      goto L20500;
   }
   if (findex_1.ormtch != 0) {
      goto L20100;
   }
// 						!ANY MATCHES LEFT?
   rspeak(183);
// 						!NO, LOSE.
   return ret_val;

L20100:
   --findex_1.ormtch;
// 						!DECREMENT NO MATCHES.
   objcts_1.oflag1[oindex_1.match - 1] |= flobts;
   cevent_1.ctick[cindex_1.cevmat - 1] = 2;
// 						!COUNTDOWN.
   rspeak(184);
   return ret_val;

L20500:
   if (prsvec_1.prsa != vindex_1.trnofw || (objcts_1.oflag1[oindex_1.match - 1] & OnO) == 0) {
      goto L10;
   }
   objcts_1.oflag1[oindex_1.match - 1] &= ~flobts;
   cevent_1.ctick[cindex_1.cevmat - 1] = 0;
   rspeak(185);
   return ret_val;

// HERE FOR FALSE RETURN

L10:
   ret_val = false;
   return ret_val;
}
