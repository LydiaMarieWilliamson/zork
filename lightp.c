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
   if (obj != oindex.candl) {
      goto L20000;
   }
// 						!CANDLE?
   if (findex.orcand != 0) {
      goto L19100;
   }
// 						!FIRST REF?
   findex.orcand = 1;
// 						!YES, CANDLES ARE
   cevent.ctick[cindex.cevcnd - 1] = 50;
// 						!BURNING WHEN SEEN.

L19100:
   if (prsvec.prsi == oindex.candl) {
      goto L10;
   }
// 						!IGNORE IND REFS.
   if (prsvec.prsa != vindex.trnofw) {
      goto L19200;
   }
// 						!TURN OFF?
   i = 513;
// 						!ASSUME OFF.
   if ((objcts.oflag1[oindex.candl - 1] & OnO) != 0) {
      i = 514;
   }
// 						!IF ON, DIFFERENT.
   cevent.cflag[cindex.cevcnd - 1] = false;
// 						!DISABLE COUNTDOWN.
   objcts.oflag1[oindex.candl - 1] &= ~OnO;
   rspeak(i);
   return ret_val;

L19200:
   if (prsvec.prsa != vindex.burnw && prsvec.prsa != vindex.trnonw) {
      goto L10;
   }
   if ((objcts.oflag1[oindex.candl - 1] & LiteO) != 0) {
      goto L19300;
   }
   rspeak(515);
// 						!CANDLES TOO SHORT.
   return ret_val;

L19300:
   if (prsvec.prsi != 0) {
      goto L19400;
   }
// 						!ANY FLAME?
   rspeak(516);
// 						!NO, LOSE.
   prsvec.prswon = false;
   return ret_val;

L19400:
   if (prsvec.prsi != oindex.match || !((objcts.oflag1[oindex.match - 1] & OnO) != 0)) {
      goto L19500;
   }
   i = 517;
// 						!ASSUME OFF.
   if ((objcts.oflag1[oindex.candl - 1] & OnO) != 0) {
      i = 518;
   }
// 						!IF ON, JOKE.
   objcts.oflag1[oindex.candl - 1] |= OnO;
   cevent.cflag[cindex.cevcnd - 1] = true;
// 						!RESUME COUNTDOWN.
   rspeak(i);
   return ret_val;

L19500:
   if (prsvec.prsi != oindex.torch || !((objcts.oflag1[oindex.torch - 1] & OnO) != 0)) {
      goto L19600;
   }
   if ((objcts.oflag1[oindex.candl - 1] & OnO) != 0) {
      goto L19700;
   }
// 						!ALREADY ON?
   newsta(oindex.candl, 521, 0, 0, 0);
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
   if (obj != oindex.match) {
      bug(6, obj);
   }
   if (prsvec.prsa != vindex.trnonw || prsvec.prso != oindex.match) {
      goto L20500;
   }
   if (findex.ormtch != 0) {
      goto L20100;
   }
// 						!ANY MATCHES LEFT?
   rspeak(183);
// 						!NO, LOSE.
   return ret_val;

L20100:
   --findex.ormtch;
// 						!DECREMENT NO MATCHES.
   objcts.oflag1[oindex.match - 1] |= flobts;
   cevent.ctick[cindex.cevmat - 1] = 2;
// 						!COUNTDOWN.
   rspeak(184);
   return ret_val;

L20500:
   if (prsvec.prsa != vindex.trnofw || (objcts.oflag1[oindex.match - 1] & OnO) == 0) {
      goto L10;
   }
   objcts.oflag1[oindex.match - 1] &= ~flobts;
   cevent.ctick[cindex.cevmat - 1] = 0;
   rspeak(185);
   return ret_val;

// HERE FOR FALSE RETURN

L10:
   ret_val = false;
   return ret_val;
}
