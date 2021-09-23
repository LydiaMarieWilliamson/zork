// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Balloon function
Bool ballop(int arg) {
// System generated locals
   Bool ret_val;

// BALLOP, PAGE 2

   ret_val = true;
// 						!ASSUME WINS.
   if (arg != 2) {
      goto L200;
   }
// 						!READOUT?
   if (prsvec.prsa != vindex.lookw) {
      goto L10;
   }
// 						!ONLY PROCESS LOOK.
   if (findex.binff != 0) {
      goto L50;
   }
// 						!INFLATED?
   rspeak(543);
// 						!NO.
   goto L100;
L50:
   rspsub(544, objcts.odesc2[findex.binff - 1]);
// 						!YES.
L100:
   if (findex.btief != 0) {
      rspeak(545);
   }
// 						!HOOKED?
   return ret_val;

L200:
   if (arg != 1) {
      goto L500;
   }
// 						!READIN?
   if (prsvec.prsa != vindex.walkw) {
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
   if (findex.btief == 0) {
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
   if (prsvec.prsa != vindex.takew || prsvec.prso != findex.binff) {
      goto L350;
   }
   rspsub(548, objcts.odesc2[findex.binff - 1]);
// 						!RECEP CONT TOO HOT.
   return ret_val;

L350:
   if (prsvec.prsa != vindex.putw || prsvec.prsi != oindex.recep || qempty(oindex.recep)) {
      goto L10;
   }
   rspeak(549);
   return ret_val;

L500:
   if (prsvec.prsa != vindex.unboaw || (rooms.rflag[play.here - 1] & LandR) == 0) {
      goto L600;
   }
   if (findex.binff != 0) {
      cevent.ctick[cindex.cevbal - 1] = 3;
   }
// 						!HE GOT OUT, START BALLOON.
   goto L10;

L600:
   if (prsvec.prsa != vindex.burnw || objcts.ocan[prsvec.prso - 1] != oindex.recep) {
      goto L700;
   }
   rspsub(550, objcts.odesc2[prsvec.prso - 1]);
// 						!LIGHT FIRE IN RECEP.
   cevent.ctick[cindex.cevbrn - 1] = objcts.osize[prsvec.prso - 1] * 20;
   objcts.oflag1[prsvec.prso - 1] |= OnO + FlamO + LiteO & ~(TakeO + ReadO);
   if (findex.binff != 0) {
      return ret_val;
   }
   if (!findex.blabf) {
      newsta(oindex.blabe, 0, 0, oindex.ballo, 0);
   }
   findex.blabf = true;
   findex.binff = prsvec.prso;
   cevent.ctick[cindex.cevbal - 1] = 3;
   rspeak(551);
   return ret_val;

L700:
   if (prsvec.prsa == vindex.unboaw && findex.binff != 0 && (rooms.rflag[play.here - 1] & LandR) != 0) {
      cevent.ctick[cindex.cevbal - 1] = 3;
   }
   goto L10;
}
