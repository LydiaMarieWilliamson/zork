// Copyright (c) 1980, InfoCom Computers and Communications, Cambridge MA 02142
// All rights reserved, commercial usage strictly prohibited.
// Written by R. M. Supnik.
// Revisions Copyright (c) 2021, Darth Spectra (Lydia Marie Williamson).
#include "extern.h"
#include "common.h"

// Troll function
Bool trollp(/*int arg*/) {
// System generated locals
   Bool ret_val;

// Local variables
   int i;

// TROLLP, PAGE 2

   ret_val = true;
// 						!ASSUME WINS.
   if (prsvec.prsa != FightW) {
      goto L1100;
   }
// 						!FIGHT?
   if (objcts.ocan[AxeOX - 1] == TrollOX) {
      goto L10;
   }
// 						!GOT AXE?  NOTHING.
   i = 433;
// 						!ASSUME CANT GET.
   if (!qhere(AxeOX, play.here)) {
      goto L1050;
   }
// 						!HERE?
   i = 434;
// 						!YES, RECOVER.
   newsta(AxeOX, 0, 0, TrollOX, 0);
L1050:
   if (qhere(TrollOX, play.here)) {
      rspeak(i);
   }
// 						!IF PLAYER HERE.
   return ret_val;

L1100:
   if (prsvec.prsa != DeadXW) {
      goto L1200;
   }
// 						!DEAD?
   findex.trollf = true;
// 						!PERMIT EXITS.
   return ret_val;

L1200:
   if (prsvec.prsa != OutXW) {
      goto L1300;
   }
// 						!OUT?
   findex.trollf = true;
// 						!PERMIT EXITS.
   objcts.oflag1[AxeOX - 1] &= ~VisiO;
   objcts.odesc1[TrollOX - 1] = 435;
// 						!TROLL OUT.
   return ret_val;

L1300:
   if (prsvec.prsa != InXW) {
      goto L1400;
   }
// 						!WAKE UP?
   findex.trollf = false;
// 						!FORBID EXITS.
   objcts.oflag1[AxeOX - 1] |= VisiO;
   objcts.odesc1[TrollOX - 1] = 436;
// 						!TROLL IN.
   if (qhere(TrollOX, play.here)) {
      rspeak(437);
   }
   return ret_val;

L1400:
   if (prsvec.prsa != FrstQW) {
      goto L1500;
   }
// 						!FIRST ENCOUNTER?
   ret_val = prob(33, 66);
// 						!33% TRUE UNLESS BADLK.
   return ret_val;

L1500:
   if (prsvec.prsa != MoveW && prsvec.prsa != TakeW && prsvec.prsa != MungW && prsvec.prsa != ThrowW && prsvec.prsa != GiveW) {
      goto L2000;
   }
   if (objcts.ocapac[TrollOX - 1] >= 0) {
      goto L1550;
   }
// 						!TROLL OUT?
   objcts.ocapac[TrollOX - 1] = -objcts.ocapac[TrollOX - 1];
// 						!YES, WAKE HIM.
   objcts.oflag1[AxeOX - 1] |= VisiO;
   findex.trollf = false;
   objcts.odesc1[TrollOX - 1] = 436;
   rspeak(437);

L1550:
   if (prsvec.prsa != TakeW && prsvec.prsa != MoveW) {
      goto L1600;
   }
   rspeak(438);
// 						!JOKE.
   return ret_val;

L1600:
   if (prsvec.prsa != MungW) {
      goto L1700;
   }
// 						!MUNG?
   rspeak(439);
// 						!JOKE.
   return ret_val;

L1700:
   if (prsvec.prso == 0) {
      goto L10;
   }
// 						!NO OBJECT?
   i = 440;
// 						!ASSUME THROW.
   if (prsvec.prsa == GiveW) {
      i = 441;
   }
// 						!GIVE?
   rspsub(i, objcts.odesc2[prsvec.prso - 1]);
// 						!TROLL TAKES.
   if (prsvec.prso == KnifeOX) {
      goto L1900;
   }
// 						!OBJ KNIFE?
   newsta(prsvec.prso, 442, 0, 0, 0);
// 						!NO, EATS IT.
   return ret_val;

L1900:
   rspeak(443);
// 						!KNIFE, THROWS IT BACK
   objcts.oflag2[TrollOX - 1] |= FiteO;
   return ret_val;

L2000:
   if (!findex.trollf || prsvec.prsa != HelloW) {
      goto L10;
   }
   rspeak(366);
// 						!TROLL OUT.
   return ret_val;

L10:
   ret_val = false;
// 						!COULDNT HANDLE IT.
   return ret_val;
}

// Cyclops function
Bool cyclop(/*int arg*/) {
// System generated locals
   int i__1, i__2;
   Bool ret_val;

// Local variables
   int i;

// CYCLOP, PAGE 2

   ret_val = true;
// 						!ASSUME WINS.
   if (!findex.cyclof) {
      goto L100;
   }
// 						!ASLEEP?
   if (prsvec.prsa != AlarmW && prsvec.prsa != MungW && prsvec.prsa != HelloW && prsvec.prsa != BurnW && prsvec.prsa != KillW && prsvec.prsa != AttacW) {
      goto L10;
   }
   findex.cyclof = false;
// 						!WAKE CYCLOPS.
   rspeak(187);
// 						!DESCRIBE.
   findex.rvcyc = abs(findex.rvcyc);
   objcts.oflag2[CycloOX - 1] = (objcts.oflag2[CycloOX - 1] | FiteO) & ~SlepO;
   return ret_val;

L100:
   if (prsvec.prsa == FightW || prsvec.prsa == FrstQW) {
      goto L10;
   }
   if (abs(findex.rvcyc) <= 5) {
      goto L200;
   }
// 						!ANNOYED TOO MUCH?
   findex.rvcyc = 0;
// 						!RESTART COUNT.
   jigsup(188);
// 						!YES, EATS PLAYER.
   return ret_val;

L200:
   if (prsvec.prsa != GiveW) {
      goto L500;
   }
// 						!GIVE?
   if (prsvec.prso != FoodOX || findex.rvcyc < 0) {
      goto L300;
   }
// 						!FOOD WHEN HUNGRY?
   newsta(FoodOX, 189, 0, 0, 0);
// 						!EATS PEPPERS.
// Computing MIN
   i__1 = -1, i__2 = -findex.rvcyc;
   findex.rvcyc = min(i__1, i__2);
// 						!GETS THIRSTY.
   return ret_val;

L300:
   if (prsvec.prso != WaterOX) {
      goto L400;
   }
// 						!DRINK WHEN THIRSTY?
   if (findex.rvcyc >= 0) {
      goto L350;
   }
   newsta(prsvec.prso, 190, 0, 0, 0);
// 						!DRINKS AND
   findex.cyclof = true;
// 						!FALLS ASLEEP.
   objcts.oflag2[CycloOX - 1] = (objcts.oflag2[CycloOX - 1] | SlepO) & ~FiteO;
   return ret_val;

L350:
   rspeak(191);
// 						!NOT THIRSTY.
L10:
   ret_val = false;
// 						!FAILS.
   return ret_val;

L400:
   i = 192;
// 						!ASSUME INEDIBLE.
   if (prsvec.prso == GarliOX) {
      i = 193;
   }
// 						!GARLIC IS JOKE.
L450:
   rspeak(i);
// 						!DISDAIN IT.
   if (findex.rvcyc < 0) {
      --findex.rvcyc;
   }
   if (findex.rvcyc >= 0) {
      ++findex.rvcyc;
   }
   if (!findex.cyclof) {
      i__1 = abs(findex.rvcyc) + 193;
      rspeak(i__1);
   }
   return ret_val;

L500:
   i = 0;
// 						!ASSUME NOT HANDLED.
   if (prsvec.prsa == HelloW) {
      goto L450;
   }
// 						!HELLO IS NO GO.
   if (prsvec.prsa == ThrowW || prsvec.prsa == MungW) {
      i = rnd(2) + 200;
   }
   if (prsvec.prsa == TakeW) {
      i = 202;
   }
   if (prsvec.prsa == TieW) {
      i = 203;
   }
   if (i <= 0) {
      goto L10;
   } else {
      goto L450;
   }
// 						!SEE IF HANDLED.
}

// Thief function
Bool thiefp(/*int arg*/) {
// System generated locals
   int i__1;
   Bool ret_val;

// Local variables
   int i, j;

// THIEFP, PAGE 2

   ret_val = true;
// 						!ASSUME WINS.
   if (prsvec.prsa != FightW) {
      goto L100;
   }
// 						!FIGHT?
   if (objcts.ocan[StillOX - 1] == ThiefOX) {
      goto L10;
   }
// 						!GOT STILLETTO?  F.
   if (qhere(StillOX, hack.thfpos)) {
      goto L50;
   }
// 						!CAN HE RECOVER IT?
   newsta(ThiefOX, 0, 0, 0, 0);
// 						!NO, VANISH.
   if (qhere(ThiefOX, play.here)) {
      rspeak(498);
   }
// 						!IF HERO, TELL.
   return ret_val;

L50:
   newsta(StillOX, 0, 0, ThiefOX, 0);
// 						!YES, RECOVER.
   if (qhere(ThiefOX, play.here)) {
      rspeak(499);
   }
// 						!IF HERO, TELL.
   return ret_val;

L100:
   if (prsvec.prsa != DeadXW) {
      goto L200;
   }
// 						!DEAD?
   hack.thfact = false;
// 						!DISABLE DEMON.
   objcts.oflag1[ChaliOX - 1] |= TakeO;
   j = 0;
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!CARRYING ANYTHING?
// L125:
      if (objcts.oadv[i - 1] == -ThiefOX) {
         j = 500;
      }
   }
   rspeak(j);
// 						!TELL IF BOOTY REAPPEARS.

   j = 501;
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
// 						!LOOP.
      if (i == ChaliOX || i == ThiefOX || play.here != TreasRX || !qhere(i, play.here)) {
         goto L135;
      }
      objcts.oflag1[i - 1] |= VisiO;
      rspsub(j, objcts.odesc2[i - 1]);
// 						!DESCRIBE.
      j = 502;
      goto L150;

   L135:
      if (objcts.oadv[i - 1] == -ThiefOX) {
         newsta(i, 0, play.here, 0, 0);
      }
   L150:
      ;
   }
   return ret_val;

L200:
   if (prsvec.prsa != FrstQW) {
      goto L250;
   }
// 						!FIRST ENCOUNTER?
   ret_val = prob(20, 75);
   return ret_val;

L250:
   if (prsvec.prsa != HelloW || objcts.odesc1[ThiefOX - 1] != 504) {
      goto L300;
   }
   rspeak(626);
   return ret_val;

L300:
   if (prsvec.prsa != OutXW) {
      goto L400;
   }
// 						!OUT?
   hack.thfact = false;
// 						!DISABLE DEMON.
   objcts.odesc1[ThiefOX - 1] = 504;
// 						!CHANGE DESCRIPTION.
   objcts.oflag1[StillOX - 1] &= ~VisiO;
   objcts.oflag1[ChaliOX - 1] |= TakeO;
   return ret_val;

L400:
   if (prsvec.prsa != InXW) {
      goto L500;
   }
// 						!IN?
   if (qhere(ThiefOX, play.here)) {
      rspeak(505);
   }
// 						!CAN HERO SEE?
   hack.thfact = true;
// 						!ENABLE DEMON.
   objcts.odesc1[ThiefOX - 1] = 503;
// 						!CHANGE DESCRIPTION.
   objcts.oflag1[StillOX - 1] |= VisiO;
   if (play.here == TreasRX && qhere(ChaliOX, play.here)) {
      objcts.oflag1[ChaliOX - 1] &= ~TakeO;
   }
   return ret_val;

L500:
   if (prsvec.prsa != TakeW) {
      goto L600;
   }
// 						!TAKE?
   rspeak(506);
// 						!JOKE.
   return ret_val;

L600:
   if (prsvec.prsa != ThrowW || prsvec.prso != KnifeOX || (objcts.oflag2[ThiefOX - 1] & FiteO) != 0) {
      goto L700;
   }
   if (prob(10, 10)) {
      goto L650;
   }
// 						!THREW KNIFE, 10%?
   rspeak(507);
// 						!NO, JUST MAKES
   objcts.oflag2[ThiefOX - 1] |= FiteO;
   return ret_val;

L650:
   j = 508;
// 						!THIEF DROPS STUFF.
   i__1 = objcts.olnt;
   for (i = 1; i <= i__1; ++i) {
      if (objcts.oadv[i - 1] != -ThiefOX) {
         goto L675;
      }
// 						!THIEF CARRYING?
      j = 509;
      newsta(i, 0, play.here, 0, 0);
   L675:
      ;
   }
   newsta(ThiefOX, j, 0, 0, 0);
// 						!THIEF VANISHES.
   return ret_val;

L700:
   if (prsvec.prsa != ThrowW && prsvec.prsa != GiveW || prsvec.prso == 0 || prsvec.prso == ThiefOX) {
      goto L10;
   }
   if (objcts.ocapac[ThiefOX - 1] >= 0) {
      goto L750;
   }
// 						!WAKE HIM UP.
   objcts.ocapac[ThiefOX - 1] = -objcts.ocapac[ThiefOX - 1];
   hack.thfact = true;
   objcts.oflag1[StillOX - 1] |= VisiO;
   objcts.odesc1[ThiefOX - 1] = 503;
   rspeak(510);

L750:
   if (prsvec.prso != BrickOX || objcts.ocan[FuseOX - 1] != BrickOX || cevent.ctick[FusCX - 1] == 0) {
      goto L800;
   }
   rspeak(511);
// 						!THIEF REFUSES BOMB.
   return ret_val;

L800:
   i__1 = -ThiefOX;
   newsta(prsvec.prso, 0, 0, 0, i__1);
// 						!THIEF TAKES GIFT.
   if (objcts.otval[prsvec.prso - 1] > 0) {
      goto L900;
   }
// 						!A TREASURE?
   rspsub(512, objcts.odesc2[prsvec.prso - 1]);
   return ret_val;

L900:
   rspsub(627, objcts.odesc2[prsvec.prso - 1]);
// 						!THIEF ENGROSSED.
   findex.thfenf = true;
   return ret_val;

L10:
   ret_val = false;
   return ret_val;
}
