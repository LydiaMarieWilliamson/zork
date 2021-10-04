// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Balloon function
bool ballop(int arg) {
// System generated locals
   bool ret_val;

// BALLOP, PAGE 2

   ret_val = true;
// 						!ASSUME WINS.
   if (arg != 2) {
      goto L200;
   }
// 						!READOUT?
   if (prsvec.prsa != LookW) {
      goto L10;
   }
// 						!ONLY PROCESS LOOK.
   if (findex_1.binff != 0) {
      goto L50;
   }
// 						!INFLATED?
   rspeak(543);
// 						!NO.
   goto L100;
L50:
   rspsub(544, objcts.odesc2[findex_1.binff - 1]);
// 						!YES.
L100:
   if (findex_1.btief != 0) {
      rspeak(545);
   }
// 						!HOOKED?
   return ret_val;

L200:
   if (arg != 1) {
      goto L500;
   }
// 						!READIN?
   if (prsvec.prsa != WalkW) {
      goto L300;
   }
// 						!WALK?
   if (findxt(prsvec.prso, play.here)) {
      goto L250;
   }
// 						!VALID EXIT?
   rspeak(546);
// 						!NO, JOKE.
   return ret_val;

L250:
   if (findex_1.btief == 0) {
      goto L275;
   }
// 						!TIED UP?
   rspeak(547);
// 						!YES, JOKE.
   return ret_val;

L275:
   if (curxt.xtype != xpars.xnorm) {
      goto L10;
   }
// 						!NORMAL EXIT?
   if ((rooms.rflag[curxt.xroom1 - 1] & MungR) == 0) {
      state.bloc = curxt.xroom1;
   }
L10:
   ret_val = false;
   return ret_val;

L300:
   if (prsvec.prsa != TakeW || prsvec.prso != findex_1.binff) {
      goto L350;
   }
   rspsub(548, objcts.odesc2[findex_1.binff - 1]);
// 						!RECEP CONT TOO HOT.
   return ret_val;

L350:
   if (prsvec.prsa != PutW || prsvec.prsi != RecepOX || qempty(RecepOX)) {
      goto L10;
   }
   rspeak(549);
   return ret_val;

L500:
   if (prsvec.prsa != UnboaW || (rooms.rflag[play.here - 1] & LandR) == 0) {
      goto L600;
   }
   if (findex_1.binff != 0) {
      cevent.ctick[BalCX - 1] = 3;
   }
// 						!HE GOT OUT, START BALLOON.
   goto L10;

L600:
   if (prsvec.prsa != BurnW || objcts.ocan[prsvec.prso - 1] != RecepOX) {
      goto L700;
   }
   rspsub(550, objcts.odesc2[prsvec.prso - 1]);
// 						!LIGHT FIRE IN RECEP.
   cevent.ctick[BrnCX - 1] = objcts.osize[prsvec.prso - 1] * 20;
   objcts.oflag1[prsvec.prso - 1] |= OnO + FlamO + LiteO & ~(TakeO + ReadO);
   if (findex_1.binff != 0) {
      return ret_val;
   }
   if (!findex_0.blabf) {
      newsta(BlaBeOX, 0, 0, BalloOX, 0);
   }
   findex_0.blabf = true;
   findex_1.binff = prsvec.prso;
   cevent.ctick[BalCX - 1] = 3;
   rspeak(551);
   return ret_val;

L700:
   if (prsvec.prsa == UnboaW && findex_1.binff != 0 && (rooms.rflag[play.here - 1] & LandR) != 0) {
      cevent.ctick[BalCX - 1] = 3;
   }
   goto L10;
}
