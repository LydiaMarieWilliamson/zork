// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Light processor
bool lightp(int obj) {
// System generated locals
   bool ret_val;

// Local variables
   int flobts;
   int i;

// LIGHTP, PAGE 2

   ret_val = true;
// 						!ASSUME WINS
   flobts = FlamO + LiteO + OnO;
   if (obj != CandlOX) {
      goto L20000;
   }
// 						!CANDLE?
   if (findex_1.orcand != 0) {
      goto L19100;
   }
// 						!FIRST REF?
   findex_1.orcand = 1;
// 						!YES, CANDLES ARE
   cevent.ctick[CndCX - 1] = 50;
// 						!BURNING WHEN SEEN.

L19100:
   if (prsvec.prsi == CandlOX) {
      goto L10;
   }
// 						!IGNORE IND REFS.
   if (prsvec.prsa != TrnOfW) {
      goto L19200;
   }
// 						!TURN OFF?
   i = 513;
// 						!ASSUME OFF.
   if ((objcts.oflag1[CandlOX - 1] & OnO) != 0) {
      i = 514;
   }
// 						!IF ON, DIFFERENT.
   cevent.cflag[CndCX - 1] = false;
// 						!DISABLE COUNTDOWN.
   objcts.oflag1[CandlOX - 1] &= ~OnO;
   rspeak(i);
   return ret_val;

L19200:
   if (prsvec.prsa != BurnW && prsvec.prsa != TrnOnW) {
      goto L10;
   }
   if ((objcts.oflag1[CandlOX - 1] & LiteO) != 0) {
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
   if (prsvec.prsi != MatchOX || !((objcts.oflag1[MatchOX - 1] & OnO) != 0)) {
      goto L19500;
   }
   i = 517;
// 						!ASSUME OFF.
   if ((objcts.oflag1[CandlOX - 1] & OnO) != 0) {
      i = 518;
   }
// 						!IF ON, JOKE.
   objcts.oflag1[CandlOX - 1] |= OnO;
   cevent.cflag[CndCX - 1] = true;
// 						!RESUME COUNTDOWN.
   rspeak(i);
   return ret_val;

L19500:
   if (prsvec.prsi != TorchOX || !((objcts.oflag1[TorchOX - 1] & OnO) != 0)) {
      goto L19600;
   }
   if ((objcts.oflag1[CandlOX - 1] & OnO) != 0) {
      goto L19700;
   }
// 						!ALREADY ON?
   newsta(CandlOX, 521, 0, 0, 0);
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
   if (obj != MatchOX) {
      bug(6, obj);
   }
   if (prsvec.prsa != TrnOnW || prsvec.prso != MatchOX) {
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
   objcts.oflag1[MatchOX - 1] |= flobts;
   cevent.ctick[MatCX - 1] = 2;
// 						!COUNTDOWN.
   rspeak(184);
   return ret_val;

L20500:
   if (prsvec.prsa != TrnOfW || (objcts.oflag1[MatchOX - 1] & OnO) == 0) {
      goto L10;
   }
   objcts.oflag1[MatchOX - 1] &= ~flobts;
   cevent.ctick[MatCX - 1] = 0;
   rspeak(185);
   return ret_val;

// HERE FOR FALSE RETURN

L10:
   ret_val = false;
   return ret_val;
}
