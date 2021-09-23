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
   if (prsvec_1.prsa != vindex_1.lookw) {
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
   rspsub(544, objcts_1.odesc2[findex_1.binff - 1]);
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
   if (prsvec_1.prsa != vindex_1.walkw) {
      goto L300;
   }
// 						!WALK?
   if (findxt(prsvec_1.prso, play_1.here)) {
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
   if (curxt_1.xtype != xpars_1.xnorm) {
      goto L10;
   }
// 						!NORMAL EXIT?
   if ((rooms_1.rflag[curxt_1.xroom1 - 1] & MungR) == 0) {
      state_1.bloc = curxt_1.xroom1;
   }
L10:
   ret_val = false;
   return ret_val;

L300:
   if (prsvec_1.prsa != vindex_1.takew || prsvec_1.prso != findex_1.binff) {
      goto L350;
   }
   rspsub(548, objcts_1.odesc2[findex_1.binff - 1]);
// 						!RECEP CONT TOO HOT.
   return ret_val;

L350:
   if (prsvec_1.prsa != vindex_1.putw || prsvec_1.prsi != oindex_1.recep || qempty(oindex_1.recep)) {
      goto L10;
   }
   rspeak(549);
   return ret_val;

L500:
   if (prsvec_1.prsa != vindex_1.unboaw || (rooms_1.rflag[play_1.here - 1] & LandR) == 0) {
      goto L600;
   }
   if (findex_1.binff != 0) {
      cevent_1.ctick[cindex_1.cevbal - 1] = 3;
   }
// 						!HE GOT OUT, START BALLOON.
   goto L10;

L600:
   if (prsvec_1.prsa != vindex_1.burnw || objcts_1.ocan[prsvec_1.prso - 1] != oindex_1.recep) {
      goto L700;
   }
   rspsub(550, objcts_1.odesc2[prsvec_1.prso - 1]);
// 						!LIGHT FIRE IN RECEP.
   cevent_1.ctick[cindex_1.cevbrn - 1] = objcts_1.osize[prsvec_1.prso - 1] * 20;
   objcts_1.oflag1[prsvec_1.prso - 1] |= OnO + FlamO + LiteO & ~(TakeO + ReadO);
   if (findex_1.binff != 0) {
      return ret_val;
   }
   if (!findex_1.blabf) {
      newsta(oindex_1.blabe, 0, 0, oindex_1.ballo, 0);
   }
   findex_1.blabf = true;
   findex_1.binff = prsvec_1.prso;
   cevent_1.ctick[cindex_1.cevbal - 1] = 3;
   rspeak(551);
   return ret_val;

L700:
   if (prsvec_1.prsa == vindex_1.unboaw && findex_1.binff != 0 && (rooms_1.rflag[play_1.here - 1] & LandR) != 0) {
      cevent_1.ctick[cindex_1.cevbal - 1] = 3;
   }
   goto L10;
}
